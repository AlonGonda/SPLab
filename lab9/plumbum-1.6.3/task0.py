from plumbum.cmd import awk, sort, uniq, wc, uniq 
print ('The students mentioned in the file are:')
students = awk("-F", "\t", "{print $1}", "lab10_grades")
print(students)

print ('The number of students mentioned in the file is:')
students_number = awk["-F", "\t", "{print $1}", "lab10_grades"]| wc["-l"]
print (students_number())

print ('The error-codes mentioned in the file:')
errors = awk ['-F',"\t",'{for(i=2; i<=NF; i++) print $i}','lab10_grades'] | awk ['-F',"|", "{for(i=1; i<=NF; i++) print $i}"] | awk ['-F',":", "{print $1}"]| sort | uniq ["-c"]
print (errors())

print ('The number of unique error-codes is:')
errors = awk ['-F',"\t",'{for(i=2; i<=NF; i++) print $i}','lab10_grades'] | awk ['-F',"|", "{for(i=1; i<=NF; i++) print $i}"] | awk ['-F',":", "{print $1}"]| sort | uniq | wc["-l"]
print (errors())
