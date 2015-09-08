import os


def listfilepath(pathname):
    filelist = []
    tmplist = os.listdir(pathname)
    for i in tmplist:
        if os.path.isfile(i)==True:
            filelist.append(i)
        else:
           filelist =  filelist + listfilepath(os.getcwd() + i)

    return filelist

list = listfilepath("D:\MyDrivers")
print(list)