using ltrace we see that the program gets the pid and tries to open a file in 
/tmp/[PID], so by using symbolic links we can get to 
/etc/behemoth_pass/behemoth5
after some trials we see that PID are going up, so by setting 3 or 4 symbolic 
links with the proper offset from current PID, and activating the program, 
we get:
Finished sleeping, fgetcing
aizeeshing
