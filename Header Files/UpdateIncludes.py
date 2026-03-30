import os

print_string = "/**\n * Makes #include directive for all .h files in current working directory\n */\n"
header_filename = "HEADERS_all.h"

entries = os.listdir(".")
# print(entries)

h_files = []

for entry in entries:
	full_path = os.path.join(".", entry)
	if entry == header_filename:
		continue
	if os.path.isfile(full_path) and entry[-2:] == ".h":
		h_files.append(entry)

# print (h_files)

for h in h_files:
	this_string = "#include \"" + h + "\"\n"
	print_string += this_string

# print(print_string)

with open(header_filename, "w") as f:
    f.write(print_string)
