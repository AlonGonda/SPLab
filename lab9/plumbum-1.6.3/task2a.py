import csv

geners_min = {}
geners_num = {}  
input_file = open ("IMDB.csv")
csvreader = csv.reader(input_file)

#get the first row (fields) and move to first row of data
next(csvreader)

data = []
for row in csvreader:
    data.append(row)

input_file.close()

for row in data:
    current_movie_geners = row[3]
    current_movie_geners = current_movie_geners.split(", ")
    for gener in current_movie_geners:
        if gener not in geners_min:
            geners_min[gener] = 0
            geners_num[gener] = 0
        geners_min[gener] = int(geners_min[gener]) + int(row[4])
        geners_num[gener] = int(geners_num[gener]) + 1

output_file = open("gener.stats.txt" , 'w' )  
for gener in geners_num:
    average = geners_min[gener]/geners_num[gener]
    output_file.write("{}|{}\n".format(gener,average))

output_file.close()