import marimo

__generated_with = "0.18.4"
app = marimo.App(width="medium")


@app.cell
def _():
    import marimo as mo
    return (mo,)


@app.cell
def _():
    import altair as alt
    import pandas as pd
    return alt, pd


@app.cell
def _():
    import ccl
    return (ccl,)


@app.cell
def _(mo):
    kp = mo.ui.slider(0, 5, step=0.1, value=1.0, label="Kp")
    ki = mo.ui.slider(0, 2, step=0.1, value=0.0, label="Ki")
    kd = mo.ui.slider(0, 2, step=0.1, value=0.0, label="Kd")

    mo.vstack([kp, ki, kd])
    return kd, ki, kp


@app.cell
def _(ccl, kd, ki, kp):
    pid = ccl.PID(kp.value, ki.value, kd.value)
    return (pid,)


@app.cell(hide_code=True)
def _(pid):
    position = 0
    velocity = 0
    target = 100
    mass = 1
    dt = 0.1
    steps = 100

    position_track = [position]
    velocity_track = [velocity]

    for _ in range(0, steps):
        force = pid.update(target, position, dt)

        acceleration = force / mass
        velocity += acceleration * dt
        position += velocity * dt

        position_track.append(position)
        velocity_track.append(velocity)
    return position_track, target


@app.cell(hide_code=True)
def _(pd, position_track, target):
    df = pd.DataFrame({
        'step': range(len(position_track)),
        'position': position_track,
        'target': [target] * len(position_track)
    })
    return (df,)


@app.cell
def _(alt, df, pd, target):
    position_line = alt.Chart(df).mark_line(color='blue').encode(
        x='step',
        y='position'
    )

    target_line = alt.Chart(pd.DataFrame({'y': [target]})).mark_rule(
        color='red', 
        strokeDash=[5, 5]
    ).encode(y='y')

    (position_line + target_line).properties(width=600, height=300)
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
