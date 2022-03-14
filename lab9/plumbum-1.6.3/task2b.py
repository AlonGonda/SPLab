import csv
import sys

geners = {} 
input_file = open ("IMDB.csv")
csvreader = csv.reader(input_file)

#get the first row (fields) and move to first row of data
next(csvreader)

data = []
for row in csvreader:
    data.append(row)

input_file.close()

for row in data:
    current_movie_countries = row[5]
    current_movie_countries = current_movie_countries.split(", ")
    for country in current_movie_countries:
        if country == sys.argv[1]:
            current_movie_gener = row[3]
            current_movie_gener = current_movie_gener.split(", ")
            for gener in current_movie_gener:
                if gener not in geners:
                    geners[gener] = 0
                geners[gener] = geners[gener] + 1
 
for gener in geners:
    print("{}|{}".format(gener,geners[gener]))
