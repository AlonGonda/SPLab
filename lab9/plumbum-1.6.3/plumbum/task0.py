from plumbum.cmd import awk, sort, uniq, wc, uniq 
print ('The students mentioned in the file are:')
students = awk("-F", "\t", "{print $1}", "lab10_grades")
print(students)