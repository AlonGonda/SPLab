import matplotlib.pyplot as plt
import numpy as np
import csv
import sys


years = [] 
min_year = 0
max_year = 0
input_file = open ("IMDB.csv")
csvreader = csv.reader(input_file)

#get the first row (fields) and move to first row of data
next(csvreader)

data = []
for row in csvreader:
    data.append(row)

input_file.close()

for row in data:
    years.append(row[2])
    if int(row[2]) < int(min_year):
        min_year = row[2]
    if int(row[2]) > int(max_year):
        max_year = row[2]

range = int(max_year) - int(min_year)
years.sort()
n, bins, patches = plt.hist(years, bins=range, edgecolor = 'k')
plt.xlabel('Year')
plt.ylabel('Number Of Movies')
plt.show()