import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        if request.form.get("submit_button") == "remove":
            remove_id = request.form.get("removeID")
            db.execute("DELETE FROM birthdays WHERE id = ?", remove_id)
        else:
            namereq = request.form.get("name")
            monthreq = request.form.get("month")
            dayreq = request.form.get("day")

            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", namereq, monthreq, dayreq)
        return redirect("/")

    else:

        infos = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", infos=infos)


