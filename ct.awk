#!/bin/awk -f
/\[/ {
	gsub(/[\[\]]/, "")
	code[length(code)] = $0
	next
}
/./{
	gsub(/"/, "\\\"")
	data[length(data)] = "\""$0"\\n\""
	i=length(data)-1
	code[length(code)] = "fwrite(data"i", sizeof(data"i")-1, 1, stdout);"
}
END {
        print "#include <stdio.h>"
	print ""
	for (i=0; i < length(data); i++)
		print "static char data"i"[] = "data[i]";"
        print ""
	for (i=0; i < length(code); i++)
		print code[i]
}
