# Github edit
from os import scandir
from datetime import datetime


def convert_date(timestamp):
    d = datetime.utcfromtimestamp(timestamp)
    formated_date = d.strftime('%d %b %Y')
    return formated_date

def get_files():
    dir_entries = scandir('/home/ronald/Downloads')
    for entry in dir_entries:
        if entry.is_file():
            info = entry.stat()
            print(f'Modified: {convert_date(info.st_mtime)} \t {entry.name}\t ')

get_files()
