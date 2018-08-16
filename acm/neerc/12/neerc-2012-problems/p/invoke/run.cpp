#include "invoke.h"
#include "error.h"

#include <windows.h>
#include <conio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// ------ constants ------

static const int ESCAPE = 27;
static const int INTERACT_SIGNAL_CODE = 10;
static const int WAIT_INTERACT_SECS = 2;
static const char CMD_LINE_DELIMITER = '=';

static const int FAIL_EXIT_CODE = 0x80000000;

// ------ utility functions ------

inline int atoi(const string s) {
  return atoi(s.c_str());
}

inline double atod(const string s) {
  return atof(s.c_str());
}

inline string itoa(int i) {
    char buf[20];
    sprintf_s(buf, "%d", i);
    return string(buf);
}

inline string itoa(int64 i) {
    char buf[20];
    sprintf_s(buf, "%I64d", i);
    return string(buf);
}

inline string itoa(int i, int digit_number) {
    char buf[20];
    sprintf_s(buf, (string("%") + itoa(digit_number) + "i").c_str(), i);
    return string(buf);
}

inline string ftoa(double f, int total_number, int digit_number) {
    char buf[20];
    sprintf_s(buf, (string("%") + itoa(total_number) + "." + itoa(digit_number) + "f").c_str(), f);
    string r = buf;
    return r;
}

inline void lower(string& s) {
    int l = (int) s.length();
    for (int i = 0; i < l; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 'a' - 'A';
    }
}

string trim(string s) {
    string::size_type pos = s.find_last_not_of(' ');
    if (pos == string::npos) {
        return "";
    }

    s.erase(pos + 1);

    pos = s.find_first_not_of(' ');
    if (pos != string::npos) {
        s.erase(0, pos);
    }

    return s;
}

// ------ utility classes ------

/**
 * Single statistics element.
 */
class StatisticsItem {
    private:

    /** Item name. */
    const string name;

    /** Value of the item on last invocation. */
    int64 lastValue;

    /** Minimal item value. */
    int64 minValue;

    /** Maximal item value. */
    int64 maxValue;

    /** Total item value. */
    int64 totalValue;

    public:

    /**
     * Creates a new statistics item.
     *
     * @param item name.
     */
    StatisticsItem(string _name) :
        name(_name),
        lastValue(0),
        minValue(0),
        maxValue(0),
        totalValue(0)
    {}

    /**
     * Sets statistics data.
     *
     * @param lastValue value on the last invocation.
     * @param minValue minimal item value.
     * @param maxValue maximal item value.
     * @param averageValue average value.
     */
    void setData(int64 lastValue, int64 minValue, int64 maxValue, int64 totalValue) {
        this->lastValue = lastValue;
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->totalValue = totalValue;
    }

    /**
     * Updates statistics item.
     *
     * @param value last value.
     */
    void update(int64 value) {
        lastValue = value;
        minValue = minValue != 0 && minValue < value ? minValue : value;
        maxValue = maxValue > value ? maxValue : value;
        totalValue += value;
    }

    /**
     * Loads data from speicified map. Keys are
     * "last.<name>" for last value,
     * "max.<name>" for maximal item value,
     * "min.<name>" for mimimal item value and
     * "total.<name>" for total item value.
     *
     * @param data map to get data from.
     */
    void loadData(map<string, string>& data) {
        setData(
            atoi(data["last." + name]),
            atoi(data["min." + name]),
            atoi(data["max." + name]),
            atoi(data["total." + name])
        );
    }

    /**
     * Saves data to map.
     *
     * @param data map to save data to.
     */
    void saveData(map<string, string>& data, int incarnations) {
        data["last." + name] = itoa(lastValue);
        data["min." + name] = itoa(minValue);
        data["max." + name] = itoa(maxValue);
        data["total." + name] = itoa(totalValue);
        data["average." + name] = ftoa(totalValue / (double)  incarnations, 0, 3);
    }
};

/**
 * Invocations statistics.
 */
class Statistics {
    private:

    /** Number of invocations performed. */
    int invocations;

    /** Consumed time statistics. */
    StatisticsItem timeConsumed;

    /** Passed time statistics. */
    StatisticsItem timePassed;

    /** Consumed memory statistics. */
    StatisticsItem memoryConsumed;

    public:

    /**
     * Creates empty statistics.
     */
    Statistics() :
        timeConsumed("timeConsumed"),
        timePassed("timePassed"),
        memoryConsumed("memoryConsumed")
    {}

    /**
     * Sets statistics data.
     *
     * @param data to set.
     */
    void setData(map<string, string> data) {
        invocations = atoi(data["invocations"]);
        timeConsumed.loadData(data);
        timePassed.loadData(data);
        memoryConsumed.loadData(data);
    }

    /**
     * Sets statistics data.
     *
     * @param data to set.
     */
    map<string, string> getData() {
        map<string, string> data;
        data["invocations"] = itoa(invocations);
        timeConsumed.saveData(data, invocations);
        timePassed.saveData(data, invocations);
        memoryConsumed.saveData(data, invocations);
        return data;
    }

    /**
     * Updates statistics.
     *
     * @result last invocation result.
     */
    void update(InvocationResult& result) {
        invocations++;
        timeConsumed.update(result.timeConsumed);
        timePassed.update(result.timePassed);
        memoryConsumed.update(result.peakMemoryConsumed);
    }
};

// ------ utility functions for properties ------

map<string, string> loadProperties(istream& in) {
    map<string, string> properties;
    while (!in.eof()) {
        string line;
        getline(in, line);
        if (line.length() == 0 || line[0] == '#') {
            continue;
        }
        string::size_type index = line.find("=");
        if (index == string::npos) {
            cerr << "Invalid property line: " + line << endl;
            continue;
        }
        string key = trim(line.substr(0, index));
        string value = trim(line.substr(index + 1));
        if (properties.find(key) != properties.end()) {
            cerr << "Duplicate value for key " + key << endl;
        }
        properties[key] = value;
    }
    return properties;
}

map<string, string> loadPropertiesFromFile(char* name) {
    ifstream in(name);
    if (!in.good()) {
        return map<string, string>();
    }
    return loadProperties(in);
}

void saveProperties(map<string, string>& properties, ostream& out) {
    typedef map<string, string>::iterator iterator;
    for (iterator i = properties.begin(); i != properties.end(); i++) {
        out << i->first << "=" << i->second << endl;
    }
}

void savePropertiesToFile(map<string, string>& properties, char* name) {
    ofstream out(name);
    return saveProperties(properties, out);
}

// ------ static data ------

static vector<string> program;

static InvocationRequest ip;         // Invocation for program
static InvocationResult ir;          // Result for program

static boolean quiet = false;
static boolean status = true;
static boolean returnExitCode = false;

static vector<char*> environment;
static Statistics statistics;
static char* statisticsFile;

// ------ static data for interactive mode only ------

static vector<string> interact;

static InvocationRequest ipInteract; // Invocation for interact
static InvocationResult irInteract;  // Result for interact

static StandardHandles sh;           // Handles for program (in interactive mode)
static StandardHandles shInteract;   // Handles for interact

static HANDLE hInteractThread;
static volatile bool doTerminateProgram;  
static volatile bool doTerminateInteract;

// ------ console output ------

void WriteXY(int attr, int x, int y, const string& s) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c; c.X = x; c.Y = y;
    DWORD d;
    unsigned short* a = new unsigned short[s.length()];
    int l = (int) s.length();
    for (int i = 0; i < l; i++) {
        a[i] = attr;
    }
    WriteConsoleOutputAttribute(h, a, l, c, &d);
    WriteConsoleOutputCharacter(h, s.c_str(), l, c, &d);
    delete[] a;
}

bool showStatus(InvocationStatus* is) {
	if (!status)
		return false; // not showing status

    if (_kbhit()) {
        if (_getch() == ESCAPE) {
            return true;
        }
    }
    string s;
    s = "  Running:     " + ftoa(is->timeConsumed / 1000.0, 2, 2);
    if (ip.timeLimit > 0) {
        s += " of " + ftoa(ip.timeLimit / 1000.0, 0, 2);
    }
    s += " (passed: " +  ftoa(is->timePassed / 1000.0, 2, 2) + ")  ";
    string sb;
    for (size_t i = 0; i < s.length(); i++) {
        sb = sb + ' ';
    }

    string t = "  Memory used: " + itoa(is->currentMemoryConsumed / 1024) + "K";
    if (ip.memoryLimit > 0) {
        t += " of " + itoa(ip.memoryLimit / 1024) + "K";
    }
    t += " (peak: " + itoa(is->peakMemoryConsumed / 1024) + "K)  ";
    while (s.length() < t.length()) {
        s += ' ';
    }
    while (t.length() < s.length()) {
        t += ' ';
    }

    int wid = (int) s.length();

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);
    int swid = csbi.dwSize.X;

    int attr = 0x1f;
    switch (is->state) {
        case PREPARING: attr = 0x0f; break;
        case RUNNING: attr = 0x5f; break;
        case CRASHED: attr = 0x4f; break;
        case IDLE: attr = 0x8f; break;
        case TERMINATING: attr = 0x2f; break;
        case TERMINATED: attr = 0x2f; break;
    }

    WriteXY(attr, swid - wid, 0, sb);
    WriteXY(attr, swid - wid, 1, s);
    WriteXY(attr, swid - wid, 2, t);
    WriteXY(attr, swid - wid, 3, sb);

    return false;
}

// ------ help ------

void sayHello() {
    cout << endl
         << "RUN for Windows NT, Version 3.0" << endl
         << "Copyright(c) SPb IFMO CTD Development Team, 2000-2012, Written by Andrew Stankevich" << endl
         << endl;
}

void displayHelpInformation() {
    cout << "This program runs other program for given period of time with specified " << endl
         << "  memory restrictions" << endl
         << endl
         << "Command line format:" << endl
         << "  run [<options>] <program> [<parameters>]" << endl
         << "Where options are:" << endl
         << "  -h               - show this help" << endl
         << "  -t <time-limit>  - time limit, terminate after <time-limit> seconds, you can" << endl
         << "                     add \"ms\" (without quotes) after the number to specify" << endl
         << "                     time limit in milliseconds" << endl
         << "  -m <mem-limit>   - memory limit, terminate if working set of the process" << endl
         << "                     exceeds <mem-limit> bytes, you can add K or M to specify" << endl
         << "                     memory limit in kilo- or megabytes" << endl
         << "  -r <req-load>    - required load of the processor for this process " << endl
         << "                     not to be considered idle. You can add % sign to specify" << endl
         << "                     required load in percent, default is 0.05 = 5%" << endl
         << "  -y <idle-limit>  - ildeness limit, terminate process if it did not load" << endl
         << "                     processor for at least <req-load> for <idle-limit>" << endl
         << "  -d <directory>   - make <directory> home directory for process" << endl
         << "  -l <login-name>  - create process under <login-name>" << endl
         << "  -p <password>    - logins user using <password>" << endl
         << "  -i <file>        - redirects standart input stream to the <file>" << endl
         << "  -o <file>        - redirects standart output stream to the <file>" << endl
         << "  -e <file>        - redirects standart error stream to the <file>" << endl
         << "  -x               - return exit code of the application" << endl
         << "  -q               - do not display any information on the screen" << endl
         << "  -qs              - display status pop-up only" << endl
         << "  -w               - display program window on the screen" << endl
         << "  -1               - use single CPU/CPU core" << endl
         << "  -s <file>        - store statistics in then <file>" << endl
         << "  -D <var>=<value> - sets environment variable <var> to <value>, current environment" << endl
         << "                     is completly ignored in this case" << endl
		 << "  -I <command>     - run <program> in interactive mode redirecting input and output" << endl
		 << "                     streams via pipes to <command>. -i and -o are ignored." << endl
		 << "                     Multiword <command> shall be enclosed in =...= characters." << endl
         << "Exteneded options:" << endl
         << "  -Xacp, --allow-create-processes" << endl
         << "                   - allow the created process to create new processes" << endl
         << "  -Xtfce, --terminate-on-first-chance-exceptions" << endl
         << "                   - do not ignore exceptions if they are marked as first-chance," << endl
         << "                     required for some old compilers as Borland Delphi" << endl
         << "  -Xifce, --ignore-first-chance-exceptions" << endl
         << "                   - ignore exceptions if they are marked as first-chance, default" << endl
         << "  -Xlegacy, -z" << endl
         << "                   - try to be compatible with old invoke.dll" << endl
         << "Examples:" << endl
         << "  run -t 10s -m 32M -i 10s a.exe" << endl
         << "  run -d \"C:\\My Directory\" a.exe" << endl
         << "  run -l invoker -p password a.exe" << endl
         << "  run -i input.txt -o output.txt -e error.txt a.exe" << endl
         << "  run -I =java -jar Interact.jar= a.exe" << endl;
}

void error(string msg) {
    sayHello();
    cout << "Error: " << msg << endl
         << "Use \"run -h\" to get help information" << endl;
}

// ------ parsing ------

/**
 * Parse comand line as either a single token or a list of token wrapped in = and =.
 * If rest is true, then command line is parsed till the end even if it is not wrapped.
 */
vector<string> parseCommandLine(int argc, char* argv[], int& i, bool rest = false) {
    bool wrapped = argv[i][0] == CMD_LINE_DELIMITER;
    if (wrapped)
        rest = true;
	vector<string> command;
    for (; i < argc; i++) {
        char* s = argv[i];
		bool first = command.empty();
        if (first && wrapped)
            s++;
		int len = (int) strlen(s); // cast is need for x64
        if (wrapped && s[len - 1] == CMD_LINE_DELIMITER) {
			if (len > 1)
				command.push_back(string(s, len - 1));
            break;
        }
		if (len != 0)
			command.push_back(string(s));
        if (!rest)
            break;
    }
    return command;
}

bool processCommandLine(int argc, char* argv[]) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = true;

    ip.timeLimit = 0;
    ip.memoryLimit = 0;
    ip.idlenessLimit = 0;
    ip.requiredProcessorLoad = 0.05;
    ip.inputFileName = NULL;
    ip.outputFileName = NULL;
    ip.errorFileName = NULL;
    ip.flags = 0;
    ip.directory = NULL;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        string val;
		if (arg.empty()) {
			// empty argument -- just skip it
		} else if (arg[0] != '-') {
            program = parseCommandLine(argc, argv, i, true);
			break;
        } else if (arg == "-h") {
            sayHello();
            displayHelpInformation();
            return false;
        } else  if (arg == "-t") {
            if (i == argc - 1) {
                error("expected time limit value after \"-t\"");
                return false;
            }
            val = argv[++i];
            lower(val);
            string digs = "";
            while ((val.length() > 0) && (isdigit(val[0]))) {
                digs += val[0];
                val.erase(0, 1);
            }
            ip.timeLimit = atoi(digs);
            if (val != "" && val != "ms" && val != "s" || ip.timeLimit == 0) {
                error("invalid time limit: " + digs + val);
                return false;
            }
            if (val == "s" || val == "")
                ip.timeLimit *= 1000;
        } else if (arg == "-m") {
            if (i == argc - 1) {
                error("expected memory limit value after \"-m\"");
                return false;
            }
            val = argv[++i];
            lower(val);
            string digs = "";
            while ((val.length() > 0) && (isdigit(val[0]))) {
                digs += val[0];
                val.erase(0, 1);
            }
            ip.memoryLimit = atoi(digs);
            if (val != "" && val != "k" && val != "m" || ip.memoryLimit == 0) {
                error("invalid memory limit: " + digs + val);
                return false;
            }
            if (val == "k")
                ip.memoryLimit *= 1024;
            if (val == "m")
                ip.memoryLimit *= 1024 * 1024;
        } else if (arg == "-y") {
            if (i == argc - 1) {
                error("expected idleness limit value after \"-y\"");
                return false;
            }
            val = argv[++i];
            lower(val);
            string digs = "";
            while ((val.length() > 0) && (isdigit(val[0]))) {
                digs += val[0];
                val.erase(0, 1);
            }
            ip.idlenessLimit = atoi(digs);
            if (val != "" && val != "ms" && val != "s" || ip.idlenessLimit == 0) {
                error("invalid idleness limit: " + digs + val);
                return false;
            }
            if (val == "s" || val == "")
                ip.idlenessLimit *= 1000;
        } else if (arg == "-r") {
            if (i == argc - 1) {
                error("expected required processor load value after \"-l\"");
                return false;
            }
            val = argv[++i];
            lower(val);
            string digs = "";
            while ((val.length() > 0) && (isdigit(val[0]) || (val[0] == '.'))) {
                digs += val[0];
                val.erase(0, 1);
            }
            bool invalid = false;
            try {
                ip.requiredProcessorLoad = atod(digs);
            } catch (exception) {
                invalid = true;
            }
            if ((val != "" && val != "%") || invalid) {
                error("invalid required processor load: " + digs + val);
                return false;
            }
            if (val == "%")
                ip.requiredProcessorLoad *= 100;
            if (ip.requiredProcessorLoad >= 1) {
                error("invalid required processor load: " + digs + val);
                return false;
            }
        } else if (arg == "-d") {
            if (i == argc - 1) {
                error("expected directory after \"-d\"");
                return false;
            }
            ip.directory = argv[++i];
        } else if (arg == "-l") {
            if (i == argc - 1) {
                error("expected login name after \"-l\"");
                return false;
            }
            ip.login = argv[++i];
        } else if (arg == "-p") {
            if (i == argc - 1) {
                error("expected password after \"-p\"");
                return false;
            }
            ip.password = argv[++i];
        } else if (arg == "-i") {
            if (i == argc - 1) {
                error("expected file name after \"-i\"");
                return false;
            }
            ip.inputFileName = argv[++i];
        } else if (arg == "-o") {
            if (i == argc - 1) {
                error("expected file name after \"-o\"");
                return false;
            }
            ip.outputFileName = argv[++i];
        } else if (arg == "-e") {
            if (i == argc - 1) {
                error("expected file name after \"-e\"");
                return false;
            }
            ip.errorFileName = argv[++i];
        } else if (arg == "--allow-create-processes" || arg == "-Xacp") {
            ip.flags |= INVOKE_ALLOW_CREATE_PROCESSES;
        } else if (arg == "--terminate-on-first-chance-exceptions" || arg == "-Xtfce" || arg == "-Xlegacy" || arg == "-z" ) {
            ip.flags |= INVOKE_TERMINATE_ON_FIRST_CHANCE_EXCEPTIONS;
        } else if (arg == "--ignore-first-chance-exceptions" || arg == "-Xifce") {
            //printf("%s", "ignoring first chance exceptions is now default behavior, use -Xtfce to terminate program on first chance exceptions");
        } else if (arg == "-q") {
            quiet = true;
            status = false;
        } else if (arg == "-qs") {
            quiet = true;
        } else if (arg == "-1") {
            ip.flags |= INVOKE_SET_SINGLE_AFFINITY;
        } else if (arg == "-w") {
            ip.flags |= INVOKE_SHOW_APPLICATION_WINDOW;
        } else if (arg == "-s") {
            if (i == argc - 1) {
                error("expected file name after \"-s\"");
                return false;
            }
            statisticsFile = argv[++i];
        } else if (arg == "-D") {
            if (i == argc - 1) {
                error("expected var=value after \"-D\"");
                return false;
            }
            environment.push_back(argv[++i]);
		} else if (arg == "-I") {
			if (i == argc - 1) {
				error("expected command after \"-I\"");
				return false;
			}
			i++;
			interact = parseCommandLine(argc, argv, i);
        } else if (arg == "-x") {
            returnExitCode = true;
        } else {
            error("unknown argument: \"" + arg + "\"");
            return false;
        }
    }

	if (program.empty()) {
        sayHello();
        cout << "Use \"run -h\" to get help information" << endl;
        return false;
    }

    return true;
}

void setupEnvironment() {
    if (!environment.empty()) {
        size_t length = 1;
        for (vector<char*>::iterator i = environment.begin(); i != environment.end() ; i++) {
            length += strlen(*i) + 1;
        }
        size_t size = sizeof(char) * length;
        ip.environment = (char*) malloc(size);
        char* p = ip.environment;
        for (vector<char*>::iterator i = environment.begin(); i != environment.end() ; i++) {
            p = strcpy(p, *i) + strlen(*i) + 1;
        }
        *p = 0;
    }
}

string setupCommandLine(InvocationRequest& ip, vector<string>& program) {
    string commandLine = program[0];
    ip.program = const_cast<char*> (program[0].c_str());
    ip.argc = (int) (program.size() - 1); // cast is need for x64
    ip.argv = new char*[ip.argc];
    for (unsigned int i = 1; i < program.size(); i++) {
        commandLine += " " + program[i];
        ip.argv[i - 1] = const_cast<char*> (program[i].c_str());
    }
	return commandLine;
}

// ------ interactive mode support ------

bool checkTerminateProgram(InvocationStatus* is) {
    if (doTerminateProgram) {
		return true;
	}
    return showStatus(is);
}

bool checkTerminateInteract(InvocationStatus* is) {
    if (doTerminateInteract) {
		return true;
    }
    return false;
}

DWORD WINAPI RunInteract(LPVOID lpParam) {
	invokeWithHandles(&ipInteract, &irInteract, &checkTerminateInteract, &shInteract);
    if (irInteract.exitCode != 0) {
		if (!quiet) {
			cout << "Interact command terminated with non-zero exit code " << irInteract.exitCode << ", terminating program" << endl;
		}
		doTerminateProgram = true;
	} else {
		if (!quiet) {
			cout << "Interact command terminated with zero exit code, waiting for program to terminate" << endl;
		}
	}
    return 0;
}

void setupInteract() {
	string interactCommandLine = setupCommandLine(ipInteract, interact);
	ipInteract.timeLimit = 0;
	ipInteract.memoryLimit = 0;
	ipInteract.idlenessLimit = 0;
	ipInteract.requiredProcessorLoad = 0;
	ipInteract.inputFileName = NULL;
	ipInteract.outputFileName = NULL;
	ipInteract.errorFileName = NULL;
	ipInteract.flags = 0;
	ipInteract.directory = ip.directory;

	// ignore io redirects 
	ip.inputFileName = NULL;
	ip.outputFileName = NULL;
	ip.errorFileName = NULL;
	
	// setup pipes
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = true;

	HANDLE hJuryToUserIn;
	HANDLE hJuryToUserOut;
	HANDLE hUserToJuryIn;
	HANDLE hUserToJuryOut;

	HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
	SetHandleInformation(hStdErr, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	CreatePipe(&hJuryToUserIn, &hJuryToUserOut, &sa, 0);
	CreatePipe(&hUserToJuryIn, &hUserToJuryOut, &sa, 0);

    sh.input = hJuryToUserIn;
    sh.output = hUserToJuryOut;
    sh.error = hStdErr;

    shInteract.input = hUserToJuryIn;
    shInteract.output = hJuryToUserOut;
    shInteract.error = hStdErr;

	if (!quiet) {
		cout << "Interacting with \"" << interactCommandLine << "\"" << endl;
	}

    DWORD tid;
    hInteractThread = CreateThread(NULL, 0, &RunInteract, NULL, 0, &tid);
}

// ------ main ------

int main(int argc, char* argv[]) {
    if (!processCommandLine(argc, argv)) {
        return 0x80000000;
    }

	if (!interact.empty()) {
		setupInteract();
	}

    setupEnvironment();
	string programCommandLine = setupCommandLine(ip, program);

    if (!quiet) {
        cout << "Running \"" << programCommandLine << "\"" <<
            ((ip.directory == NULL) ? "" : " in \"" + string(ip.directory) + "\"") << ", press ESC to terminate..." << endl;
    }

    if (statisticsFile != NULL) {
        statistics.setData(loadPropertiesFromFile(statisticsFile));
    }

	if (!interact.empty()) {
		// interactive invoke with handles
		invokeWithHandles(&ip, &ir, &checkTerminateProgram,	&sh);
		if (!quiet) {
			cout << "Program terminated" << endl;
		}
	    DWORD result = WaitForSingleObject(hInteractThread, WAIT_INTERACT_SECS * 1000);
		if (result == WAIT_TIMEOUT) {
			if (!quiet) {
				cout << "Program terminated more than " + itoa(WAIT_INTERACT_SECS) + " seconds ago, terminating interact command" << endl;
			}
			doTerminateInteract = true;
		}
	} else {
		// regular invoke
		invoke(&ip, &ir, &showStatus);
	}

    if (!quiet) {
        switch (ir.outcome) {
            case SUCCESS: {
                cout << "Program successfully terminated" << endl;
                cout << "  exit code:     " << ir.exitCode << endl;
                break;
            }
            case TIME_LIMIT_EXCEEDED: {
                cout << "Time limit exceeded" << endl;
                cout << "Program failed to terminate within "
                    << ftoa(ip.timeLimit / 1000.0, 0, 2)
                    << " sec" << endl;
                break;
            }
            case MEMORY_LIMIT_EXCEEDED: {
                cout << "Memory limit exceeded" << endl;
                cout << "Program tried to allocate more than "
                    << ip.memoryLimit
                    << " bytes" << endl;
                break;
            }
            case IDLENESS_LIMIT_EXCEEDED: {
                cout << "Idleness limit exceeded" << endl;
                cout << "Program utilized less than "
                    << ftoa(ip.requiredProcessorLoad * 100, 0, 2)
                    << "% of processor time for more than "
                    << ftoa(ip.idlenessLimit / 1000.0, 0, 2)
                    << " sec" << endl;
                break;
            }
            case CRASH: {
                cout << "Crash" << endl;
                cout << "  " << getExceptionName(ir.exceptionCode) << endl;
                break;
            }
            case SECURITY_VIOLATION: {
                cout << "Security violation: " << ir.comment << endl;
                break;
            }
            case USER_TERMINATED: {
				if (doTerminateProgram) 
					cout << "Program was forced to terminate by interact command" << endl;
				else
					cout << "Program was forced to terminate by pressing ESC" << endl;
                break;
            }
            default: {
                cout << "Invocation failed: " << ir.comment;
                break;
            }
        }

        cout << "  time consumed: "
            << ftoa(ir.timeConsumed / 1000.0, 0, 2);
        if (ip.timeLimit > 0) {
            cout << " of " << ftoa(ip.timeLimit / 1000.0, 0, 2);
        }
        cout << " sec" << endl;
        cout << "  time passed:   "
            << ftoa(ir.timePassed / 1000.0, 0, 2)
            << " sec" << endl;

        cout << "  peak memory:   "
            << ir.peakMemoryConsumed;
        if (ip.memoryLimit > 0) {
            cout << " of " << ip.memoryLimit;
        }
        cout << " bytes" << endl;
    }

    if (statisticsFile != NULL) {
        statistics.update(ir);
        savePropertiesToFile(statistics.getData(), statisticsFile);
    }

    int exitcode = 0;
    switch (ir.outcome) {
        case SUCCESS: {
            if (returnExitCode) {
                exitcode = ir.exitCode;
            }
            break;
        }
        case TIME_LIMIT_EXCEEDED: {
            exitcode = -1;
            break;
        }
        case MEMORY_LIMIT_EXCEEDED: {
            exitcode = -2;
            break;
        }
        case IDLENESS_LIMIT_EXCEEDED: {
            exitcode = -3;
            break;
        }
        case CRASH: {
            exitcode = -4;
            break;
        }
        case SECURITY_VIOLATION: {
            exitcode = -5;
            break;
        }
        case USER_TERMINATED: {
			if (doTerminateProgram)  {
				if (irInteract.exitCode != INTERACT_SIGNAL_CODE) {
					exitcode = FAIL_EXIT_CODE; // interact crashed
				}
			} else
				cout << "Program was forced to terminate by pressing ESC" << endl;
            break;
        }
        case FAIL: {
            exitcode = FAIL_EXIT_CODE;
            break;
        }
    }

    return exitcode;
}
