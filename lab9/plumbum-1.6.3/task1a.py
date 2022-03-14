import csv

countries = {}  
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
        if country not in countries:
            countries[country] = 0
        countries[country] = countries[country] + 1

output_file = open("movies.stats.txt" , 'w' )  
for country in countries:
    output_file.write("{}|{}\n".format(country,countries[country]))

output_file.close()