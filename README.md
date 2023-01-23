# catacross
concatenate two files across, combining them one line at a time
if the files are of different sizes in lines, the user will be prompted if they want to pad the files with empty new lines.
Prior to this, the program will prompt the user to take a backup.

for example

file_left
-line 1: hello
-line 2: an

file_right
-line 1: world
-line 2: example

combined_file
-line 1: hello world
-line 2: an example
