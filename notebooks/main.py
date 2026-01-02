import marimo

__generated_with = "0.18.4"
app = marimo.App(width="medium")


@app.cell
def _():
    import marimo as mo
    return


@app.cell
def _():
    import mylib
    return (mylib,)


@app.cell
def _(mylib):
    mylib.hello()
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
