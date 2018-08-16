from zipfile import *
import os

lsfile = os.listdir("./result")
zip_archive = ZipFile("./result/testZip.zip","w")

for f in lsfile:

    file = './result/' + f
    ext = os.path.splitext(file)[-1].lower()
    if ext == ".json":
        zip_archive.write(file)
        os.remove(file)

zip_archive.close()
