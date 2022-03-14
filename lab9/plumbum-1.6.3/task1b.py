import csv
import sys

number = 0 
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
            if row[2] > sys.argv[2]:
                number = number + 1

print (number)