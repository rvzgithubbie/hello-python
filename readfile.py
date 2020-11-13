import PySimpleGUI as sg
import random
import string
import pandas as pd 

f = pd.read_csv("/home/ronald/TC/USER/REMBER2/XY_VENT.DAT", sep="|",names=None, index_col=1, keep_default_na=False)

# print(f.values.tolist())

colcount = len(f.columns)
print ("Number of columns: " + str(len(f.columns)))
print ("Number of rows: " + str(len(f)))
print ("Range: " + str(range(len(f.columns))))
"""
    Basic use of the Table Element
"""

sg.change_look_and_feel('Light Green 1')

# ------ Some functions to help generate data for the table ------
def word():
    return ''.join(random.choice(string.ascii_lowercase) for i in range(5))
def number(max_val=1000):
    return random.randint(0, max_val)

def make_table(num_rows, num_cols):
    data = [[j for j in range(num_cols)] for i in range(num_rows)]
    data[0] = [word() for _ in range(num_cols)]
    for i in range(1, num_rows):
        data[i] = [word(), *[number() for i in range(num_cols - 1)]]
    return data

# ------ Make the Table Data ------
data = make_table(num_rows=15, num_cols=len(f.columns))
# headings = [str(data[0][x]) for x in range(len(data[0]))]
headings = [str(data[0][x]) for x in range(len(f.columns))]

# layout = [[sg.Table(values=data[1:][:], headings=headings, max_col_width=25, background_color='lightblue',

# ------ Window Layout ------
layout = [[sg.Table(values=f.values.tolist(), 
                    headings=headings, 
                    # max_col_width=35, 
                    background_color='lightblue',
                    auto_size_columns=True,
                    display_row_numbers=True,
                    justification='right',
                    row_height=18,
                    num_rows=20,
                    alternating_row_color='white',
                    vertical_scroll_only=False,
                    key='-TABLE-',
                    tooltip='This is a table')],
          [sg.Button('Read'), sg.Button('Double'), sg.Button('Change Colors')],
          [sg.Text('Read = read which rows are selected')],
          [sg.Text('Double = double the amount of data in the table')],
          [sg.Text('Change Colors = Changes the colors of rows 8 and 9')]]

# ------ Create Window ------
window = sg.Window('The Table Element', layout, size=(1200,600)).Finalize()
window.Maximize()

# ------ Event Loop ------
while True:
    event, values = window.read()
    print(event, values)
    if event is None:
        break
    if event == 'Double':
        for i in range(len(data)):
            data.append(data[i])
        window['-TABLE-'].update(values=data)
    elif event == 'Change Colors':
        window['-TABLE-'].update(row_colors=((8, 'white', 'red'), (9, 'green')))
        
window.close()
