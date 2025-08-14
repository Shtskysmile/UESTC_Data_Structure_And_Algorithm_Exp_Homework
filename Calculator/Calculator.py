import tkinter as tk
import subprocess

# 定义一个函数，当按钮被点击时调用
def on_button_click(char):
    # 如果按钮的字符是'='，则调用calculate()函数
    if char == '=':
        calculate()
    # 如果按钮的字符是'←'，则删除entry_expression中最后一个字符
    elif char == '←':
        entry_expression.delete(len(entry_expression.get())-1, tk.END)
    # 如果按钮的字符是空格，则在entry_expression中插入一个空格
    elif char == ' ':
        entry_expression.insert(tk.END, ' ')
    # 否则，在entry_expression中插入按钮的字符
    else:
        entry_expression.insert(tk.END, char)

def calculate():
    # 获取用户输入的表达式
    expression = entry_expression.get()
    # 执行命令并捕获输出
    result = subprocess.run(['main.exe'] + [expression], capture_output=True, text=True)
    # 将结果显示在标签上
    label_result.config(text="结果：" + result.stdout)
    # 清空输入框
    # entry_expression.delete(0, tk.END)

if __name__ == '__main__':
    # 创建主窗口
    root = tk.Tk()
    root.title("计算器")

    # 创建表达式输入框
    entry_expression = tk.Entry(root, width=35, borderwidth=5)
    entry_expression.grid(row=0, column=0, columnspan=4, padx=10, pady=10)

    # 创建结果标签
    label_result = tk.Label(root, text="结果：")
    label_result.grid(row=1, column=0, columnspan=4, padx=10, pady=10)

    # 创建数字和运算符按钮
    buttons = [
        ('7', 2, 0), ('8', 2, 1), ('9', 2, 2),
        ('4', 3, 0), ('5', 3, 1), ('6', 3, 2),
        ('1', 4, 0), ('2', 4, 1), ('3', 4, 2), ('0', 5, 1),
        ('+', 2, 3), ('-', 3, 3), ('*', 4, 3), ('/', 5, 3),
        ('=', 5, 2), ('←', 5, 0), (' ', 6, 1),
        ('(', 6, 0),  # 左括号按钮移到空格键旁边
        (')', 6, 2)   # 右括号按钮移到空格键旁边
    ]

    for (char, row, col) in buttons:
        button = tk.Button(root, text=char, width=10, height=2, command=lambda char=char: on_button_click(char))
        button.grid(row=row, column=col)

    # 运行主循环
    root.mainloop()
