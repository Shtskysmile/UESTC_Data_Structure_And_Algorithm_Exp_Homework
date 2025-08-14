import subprocess
import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk

def pack_file():
    filename = file_entry.get()
    arg = f"pak.exe {filename}"
    result = subprocess.call(arg, shell=True)
    status_label.config(text="Packing completed" if result == 0 else "Error occurred")

def unpack_file():
    filename = file_entry.get()
    arg = f"unpak.exe {filename}"
    result = subprocess.call(arg, shell=True)
    status_label.config(text="Unpacking completed" if result == 0 else "Error occurred")

if __name__ == "__main__":
    root = tk.Tk()
    root.title("File Packer and Unpacker")

    # Load the background image
    bg_image = Image.open("img/image.png")
    bg_image = ImageTk.PhotoImage(bg_image)
    
    # Create a canvas and set the background image
    canvas = tk.Canvas(root, width=bg_image.width(), height=bg_image.height())
    canvas.pack(fill="both", expand=True)
    canvas.create_image(0, 0, anchor="nw", image=bg_image)

    tk.Label(root, text="Please input the file you want to pack or unpack:", bg="white").place(x=20, y=20)
    
    file_entry = tk.Entry(root, width=50, bg="white")
    file_entry.place(x=20, y=60)
    
    browse_button = tk.Button(root, text="Browse", command=lambda: file_entry.insert(0, filedialog.askopenfilename()), bg="white")
    browse_button.place(x=20, y=100)
    
    pack_button = tk.Button(root, text="Pack", command=pack_file, bg="white")
    pack_button.place(x=20, y=140)
    
    unpack_button = tk.Button(root, text="Unpack", command=unpack_file, bg="white")
    unpack_button.place(x=120, y=140)
    
    status_label = tk.Label(root, text="", bg="white")
    status_label.place(x=20, y=180)
    
    root.mainloop()
