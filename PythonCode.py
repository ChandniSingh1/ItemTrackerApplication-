import re
import string


def searchSpefic(item):
    item = item.lower() #allows user to provide unput with lower casing 
    doc = open("CS210_Project_Three_Input_File.txt", "r") #opens txt files
    word_Count = 0
    for line in doc: #loops thorugh each line in the document 
        line = line.strip() #eliminates extra spacing 
        word = line.lower() # lowers casing of lines to match input just in case 
        if word == item:
            word_Count += 1 # if item is purchased more than once - word count is incremented 
    return word_Count
    doc.close() #closes doc 

def listOfItems():
    dic = {} # creates an empty dictionary
    doc = open("CS210_Project_Three_Input_File.txt", "r") #opens txt file 
    for line in doc:
        line = line.strip() #deleted extra spacing 
        if line in dic:
            dic[line] += 1 #if item is purchased more than once a vaule of that key is created 
        else:
            dic[line] = 1 # if item is on list default vaule of 1 is created
    for key, value in dic.items(): #loops thorugh dic and key to print key and value 
        print(key, '= ', value)
    doc.close() # closes doc


def create_new_doc():
    dic = {} # creates empty dictionary 
    doc = open("CS210_Project_Three_Input_File.txt", "r") #opens txt file
    new_doc = open('frequency.dat', 'w') # creates new dat file for writing 
    for line in doc: # loops though each line in origional txt file and eliminates extra spacing 
        line = line.strip()
        if line in dic:
            dic[line] += 1 #if item is purchased more than once a vaule of that key is created
        else:
            dic[line] = 1 # if item is on list default vaule of 1 is created
    for key in list (dic.keys()): #loops to dic 
        new_doc.write(str(key.capitalize()) + " " + str(dic[key]) + "\n") #writes info to file 
    doc.close() #closes txt file
    new_doc.close() # closes newly created file 
    


   
