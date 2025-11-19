import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from datetime import date, datetime
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        userCash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        userCash = userCash[0].get('cash')
        userSyms = db.execute("SELECT symbol, SUM(amount) AS total_amount FROM shares WHERE id = ? GROUP BY symbol", session["user_id"])
        prices = []
        total = userCash
        for syms in userSyms:
            dictTemp = {syms["symbol"]: lookup(syms["symbol"]).get('price')}
            prices.append(round(dictTemp[syms["symbol"]], 2))
            total += float(dictTemp[syms["symbol"]]) * float(syms["total_amount"])
        return render_template("index.html", userCash=userCash, userSyms=userSyms, total=round(total, 2), prices=prices)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        now = datetime.now()
        userSym = request.form.get("symbol")
        userShares = request.form.get("shares")
        if len(userSym) < 1 or len(userShares) < 1:
            return apology("You must fill all fields", 400)
        if len(userSym) != 4:
            return apology("Invalid Symbol", 400)
        try:
            userShares = int(userShares)
        except ValueError:
            return apology("You must type an integer on shares field", 400)
        symData = lookup(userSym)
        if not symData:
            return apology("Invalid Symbol", 400)
        userCash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        userBuy = int(symData.get('price')) * userShares
        if userCash[0].get('cash') < userBuy:
            return apology("Insufficient Balance", 400)

        db.execute("INSERT INTO shares (id, symbol, price, day, month, year, amount) VALUES (?, ?, ?, ?, ?, ?, ?)", session["user_id"], userSym.upper(), symData.get('price'), now.day, now.month, now.year, userShares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (userCash[0].get('cash') - userBuy), session["user_id"])

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        userSym = request.form.get("symbol")
        symData = lookup(userSym)
        return render_template("quoted.html", symData=symData)
    return apology("Something is wrong")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        userRes = request.form.get("username")
        userPas = request.form.get("password")
        userConf = request.form.get("password2")
        if len(userRes) < 1 or len(userPas) < 1 or len(userConf) < 1:
            return apology("You must fill all fields", 400)
        if userPas != userConf:
            return apology("The passwords must be identical", 403)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", userRes, generate_password_hash(userPas))
            return redirect("/login")
        except ValueError:
            return apology("Username already in use", 403)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")
    if request.method == "POST":
        userData = db.execute("SELECT symbol, price, amount FROM shares WHERE id = ?", session["user_id"])
        userCash = db.execute("SELECT cash FROM user WHERE id = ?", session["user_id"])
        userSym = request.form.get("syms")
        userShares = request.form.get("shares")
        userAmount = userData[0].get('amount')

        if len(userShares) or not userSym:
            return apology("You must fill all fields", 400)
        if userSym not in userData[0].get('symbol'):
            return apology("You don't have this share", 400)
        if userAmount < userShares:
            return apology("Insufficient Balance", 400)
        try:
            price = lookup(userSym)
            newCash = userCash + price * int(userShares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, session["user_id"])
            if userShares == userAmount:
                db.execute("")
            return render_template("index.html")
        except ValueError:
            return apology("Wrong Value", 400)
