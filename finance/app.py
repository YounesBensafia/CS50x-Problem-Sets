import os


import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
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


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    transdb = db.execute(
        "SELECT symbol, price, SUM(shares) as shares, price * SUM(shares) as total FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    som = 0
    for i in range(len(transdb)):
        som = transdb[i]["total"] + som
    cash = cash[0]["cash"]
    cash = round(cash, 1)
    som = som + cash
    for i in range(len(transdb)):
        transdb[i]["total"] = round(transdb[i]["total"], 2)
        transdb[i]["total"] = usd(transdb[i]["total"])
        transdb[i]["price"] = usd(transdb[i]["price"])
    return render_template("home.html", transdb=transdb, cash=usd(cash), som=usd(som))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("must provide symbol and a number of shares", 400)
        quote_data = lookup(request.form.get("symbol"))
        if not quote_data:
            return apology("Symbol doesn't exist", 400)
        try:
            if int(request.form.get("shares")) < 0:
                return apology("Provide a positive number", 400)
        except ValueError:
            return apology("Provide a integer number", 400)
        else:
            transaction = int(request.form.get("shares")) * \
                lookup(request.form.get("symbol"))["price"]
            user_id = session["user_id"]
            user_cash_rn = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
            user_cash = user_cash_rn[0]["cash"]
            if transaction > user_cash:
                return apology("You don't have enough money", 400)
            new_cash = user_cash - transaction
            db.execute("UPDATE users SET cash = ? WHERE id = ? ", new_cash, user_id)
            date = datetime.datetime.now()
            shares = int(request.form.get("shares"))
            db.execute("INSERT INTO transactions(user_id, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?)", user_id, lookup(
                request.form.get("symbol"))["symbol"], shares, lookup(request.form.get("symbol"))["price"], date)
            flash("Bought!")
            return redirect("/")

    return render_template("buy.html")


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
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        quote_data = lookup(request.form.get("symbol"))
        if not quote_data:
            return apology("Symbol doesn't exist", 400)
        quote_price = quote_data["price"]
        quote_symbol = quote_data["symbol"]
        return render_template("quote_data.html", quote_symbol=quote_symbol, quote_price=usd(quote_price))

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password not match", 400)

        try:
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", request.form.get(
                "username"), generate_password_hash(request.form.get("password")))
        except ValueError:
            return apology("Username already existes", 400)

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":

        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("must provide symbol and a number of shares", 400)

        quote_data = lookup(request.form.get("symbol"))

        if not quote_data:
            return apology("Symbol doesn't exist", 400)
        try:
            if int(request.form.get("shares")) < 0:
                return apology("Provide a positive number", 400)
        except ValueError:
            return apology("Provide a integer number", 400)

        db_select = db.execute(
            "SELECT shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, request.form.get("symbol"))

        if len(db_select) == 0:
            return apology("You don't own any stock of this", 400)
        sum = 0
        for i in range(len(db_select)):
            sum = sum + db_select[i]["shares"]
        if sum < int(request.form.get("shares")):
            return apology("You don't own that many shares of the stock", 400)
        if (sum == int(request.form.get("shares"))):
            db.execute("DELETE FROM transactions WHERE symbol = ?", request.form.get("symbol"))
        else:
            db_shares = db.execute("SELECT id, shares FROM transactions where user_id = ?", user_id)
            db_share_id = db_shares[0]["id"]
            db_share_num = db_shares[0]["shares"]
            if (db_share_num == 0):
                db_shares = db.execute(
                    "DELETE FROM transactions Where user_id = ? AND id = ?", user_id, db_share_id)
            else:
                db.execute("UPDATE transactions SET shares = ? WHERE symbol = ? AND id = ?",
                           sum-int(request.form.get("shares")), request.form.get("symbol"), db_share_id)
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash[0]["cash"] + \
            int(request.form.get("shares")) * lookup(request.form.get("symbol"))["price"]
        db.execute("UPDATE users SET cash = ? where id = ?", user_cash, user_id)
        flash("Selled!")
        return redirect("/")

    symbols = db.execute(
        "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    return render_template("sell.html", symbols=symbols)


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    user_id = session["user_id"]
    if request.method == "POST":
        db.execute("UPDATE users SET hash = ? where id = ?",
                   generate_password_hash(request.form.get("change")), user_id)
    return render_template("change.html")
