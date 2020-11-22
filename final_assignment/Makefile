main: keyForwarder.c
	gcc -Wall -o keyForwarder -lncftp -lsio -lStrn keyForwarder.c

transferDefinition:
	cp ~/dev/school/advanced_programming_ad2020/final_assignment/advcProgServiceDefinition.plist ~/Library/LaunchAgents/

load:
	launchctl load ~/Library/LaunchAgents/advcProgServiceDefinition.plist

unload:
	launchctl unload ~/Library/LaunchAgents/advcProgServiceDefinition.plist
