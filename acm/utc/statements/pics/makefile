.PHONY: pics clean

psfiles := $(patsubst %.mp,%.1,$(wildcard *.mp))

pics: $(psfiles)

%.1: %.mp
	mpost $<

clean:
	if exist *.log del *.log
	if exist *.mpx del *.mpx
	for %%a in (*.mp) do if exist %%~na.? del %%~na.?
