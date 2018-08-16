
if [ $# -lt 1 ]; then
    echo "need number of team";
    exit 1;
fi;
id=0;
n=$1;
echo $n
for (( i=1; i<=$n; ++ i))
do
    id=`expr $id + 1`
    pw=`cat /dev/urandom | tr -dc a-z | head -c 6`
    auth=`php -r "echo md5('team_$id#$pw');"`;
    while true; do
        mysql -u root -proot -e "insert into team(login,name,categoryid,authtoken,enabled) values('team_$id','team_$id',1,'$auth',1);" domjudge 2> err
        if [ $? -eq 0 ]; then
            echo "ADDED with $id";
            break;
        fi;
        echo "Skipping $id";
        id=`expr $id + 1`
    done;
    echo "team_$id $pw" >> pwds
done;


