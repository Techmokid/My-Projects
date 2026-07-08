import plotly.graph_objects as go
import numpy as np

def GeneratePoints(
    x_min=-3, x_max=3,
    z_min=-2*np.pi, z_max=2*np.pi,
    x_steps=400, z_steps=400
):
    x_vals = np.linspace(x_min, x_max, x_steps)
    z_vals = np.linspace(z_min, z_max, z_steps)

    X, Z = np.meshgrid(x_vals, z_vals)

    Y = np.exp(X + 1j * Z)

    X_flat = X.flatten()
    Y_real = Y.real.flatten()
    Y_imag = Y.imag.flatten()

    return X_flat, Y_real, Y_imag

def GenerateEulerSlice(x_min=-2, x_max=2, steps=400):
    x = np.linspace(x_min, x_max, steps)
    y = -np.exp(x)   # real part
    z = np.zeros_like(x)  # imaginary part
    return x, y, z

x_all, y_real, y_imag = GeneratePoints()
x_slice, y_slice, z_slice = GenerateEulerSlice()

fig = go.Figure()

# Main point cloud
fig.add_trace(
    go.Scatter3d(
        x=x_all,
        y=y_real,
        z=y_imag,
        mode="markers",
        marker=dict(
            size=2,
            color=y_real,
            colorscale="Viridis",
            opacity=0.4
        ),
        name="e^(x + zi)"
    )
)

# e^(x + pi*i) slice
fig.add_trace(
    go.Scatter3d(
        x=x_slice,
        y=y_slice,
        z=z_slice,
        mode="lines",
        line=dict(
            color="red",
            width=6
        ),
        name="e^(x + πi)"
    )
)

# e^(pi * i) value
fig.add_trace(
    go.Scatter3d(
        x=[0],
        y=[-1],
        z=[0],
        mode="markers",
        marker=dict(color="red", size=10),
        name="e^(πi)"
    )
)

fig.update_layout(
    scene=dict(
        xaxis_title="x",
        yaxis_title="Re",
        zaxis_title="Im"
    ),
    title="e^(x + zi) with e^(πi) slice highlighted"
)

fig.write_html("complex_exp.html", auto_play=True)
#fig.show()
