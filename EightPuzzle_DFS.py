import time as tm
g_dict_layouts = {}
g_dict_shifts = {0:[1, 3], 1:[0, 2, 4], 2:[1, 5],
                 3:[0,4,6], 4:[1,3,5,7], 5:[2,4,8],
                 6:[3,7],  7:[4,6,8], 8:[5,7]}

def swap_chr(a, i, j):
    if i > j:
        i, j = j, i
    b = a[:i] + a[j] + a[i+1:j] + a[i] + a[j+1:]
    return b

def solvePuzzle_depth(srcLayout, destLayout):
   
    src=0;dest=0
    for i in range(1,9):
        fist=0
        for j in range(0,i):
          if srcLayout[j]>srcLayout[i] and srcLayout[i]!='0':
              fist=fist+1
        src=src+fist

    for i in range(1,9):
        fist=0
        for j in range(0,i):
          if destLayout[j]>destLayout[i] and destLayout[i]!='0':
              fist=fist+1
        dest=dest+fist
    if (src%2)!=(dest%2):
        return -1, None

    g_dict_layouts[srcLayout] = -1
    stack_layouts = []
    stack_layouts.append(srcLayout)

    bFound = False
    while len(stack_layouts) > 0:
        curLayout = stack_layouts.pop()
        if curLayout == destLayout:
            break
        ind_slide = curLayout.index("0")
        lst_shifts = g_dict_shifts[ind_slide]
        for nShift in lst_shifts:
            newLayout = swap_chr(curLayout, nShift, ind_slide)

            if g_dict_layouts.get(newLayout) == None:
                g_dict_layouts[newLayout] = curLayout
                stack_layouts.append(newLayout)

    lst_steps = []
    lst_steps.append(curLayout)
    while g_dict_layouts[curLayout] != -1:
        curLayout = g_dict_layouts[curLayout]
        lst_steps.append(curLayout)
    lst_steps.reverse()
    return 0, lst_steps


if __name__ == "__main__":
    srcLayout  = "541203786"
    destLayout = "123804765"

    retCode, lst_steps = solvePuzzle_depth(srcLayout, destLayout)
    if retCode != 0:
        print("目标布局不可达")
    else:
        for nIndex in range(len(lst_steps)):
            print("step #" + str(nIndex + 1))
            print(lst_steps[nIndex][:3])
            print(lst_steps[nIndex][3:6])
            print(lst_steps[nIndex][6:])

