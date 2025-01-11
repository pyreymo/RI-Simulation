import re

import numpy as np
import pandas as pd
import plotly.express as px

# Read your log file
filename = r"build/data/2D_10x10_temp_1.000000_iter_1000.txt"
thread_length, thread_radius, gap = 0, 0, 0
out = []
with open(filename) as f:
    out = f.readlines()
    f.close()

# Convert log file to Python data structure
position_list, params_list = [], []
iter, particle_number = -1, None
box_x, box_y = 0, 0
for s in out:
    try:
        ss = re.split(r"[ \t\n]+", s.strip())
        if ss[0] == "#":
            print(f"{ss[1]} = {ss[2]}")
            if ss[1] == "BOX_X":
                box_x = np.double(ss[2])
            elif ss[1] == "BOX_Y":
                box_y = np.double(ss[2])
            elif ss[1] == "Length":
                thread_length = np.double(ss[2])
            elif ss[1] == "Radius":
                thread_radius = np.double(ss[2])
            elif ss[1] == "Gap":
                gap = np.double(ss[2])
            elif ss[1] == "N":
                particle_number = int(ss[2])
        elif ss[0] == "Iter":
            iter = int(ss[1])
        elif ss[0] == "@":  # Handle params as you wish
            pass
        elif ss[0] == "@DEN":
            for i in range(10):
                params_list.append({"iter": iter, "x": i + 1, "density": np.double(ss[1 + i])})
        else:  # Read the position of the particles
            i, x, y = s.split(",")
            position_list.append({"iter": iter, "origin": 1, "index": int(i), "x": np.double(x), "y": np.double(y)})
    except:  # If something unwanted appears in the log...
        break

# Plot the position of the particles in the external browser
fig = px.scatter(
    pd.DataFrame(position_list),
    x="x",
    y="y",
    animation_frame="iter",
    animation_group="index",
    hover_name="index",
    range_x=[0, box_x],
    range_y=[0, box_y],
    template="plotly_white",
    title=r"YOUR-TITLE-HERE",
)
fig.add_shape(type="rect", x0=0, y0=0, x1=box_x, y1=box_y)
fig.update_traces(marker=dict(size=10, line=dict(width=2, color="DarkSlateGrey")), selector=dict(mode="markers"))
fig.update_layout(yaxis=dict(scaleanchor="x"))
fig.layout.updatemenus[0].buttons[0].args[1]["frame"]["duration"] = 1
fig.layout.updatemenus[0].buttons[0].args[1]["transition"]["duration"] = 0
fig.show()

# Plot particle density distribution in the external browser
density = pd.DataFrame(params_list)
density_figure = px.line(density, x="x", y="density", animation_frame="iter", range_x=[1, 10], range_y=[0, 1], markers=True, template="plotly_white")
density_figure.add_shape(type="line", x0=1, y0=0.7, x1=10, y1=0.7, line=dict(width=4, dash="dashdot"))
density_figure.show()
