import os


def listfilepath(pathname):
    filelist = []
    tmplist = os.listdir(pathname)
    for i in tmplist:
        name = pathname+"\\"+i
        if os.path.isfile(name)==True:
            filelist.append(name)
        else:
           filelist =  filelist + listfilepath(name)
    return filelist

list = listfilepath("D:\MyDrivers")
print(list)