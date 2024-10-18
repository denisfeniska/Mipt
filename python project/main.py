import yfinance as yf
import sqlite3
from getpass import getpass

# Создание базы данных для пользователей и сделок
conn = sqlite3.connect('trading_platform.db')
cursor = conn.cursor()

# Создаем таблицу пользователей
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE,
    password TEXT,
    balance REAL DEFAULT 10000.0
)''')

# Создаем таблицу для хранения истории сделок
cursor.execute('''CREATE TABLE IF NOT EXISTS trades (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    stock_symbol TEXT,
    price REAL,
    quantity REAL,
    trade_type TEXT,
    FOREIGN KEY(user_id) REFERENCES users(id)
)''')

conn.commit()

# Функции для работы с пользователями
def register_user(username, password):
    try:
        cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, password))
        conn.commit()
        print("Регистрация успешна!")
    except sqlite3.IntegrityError:
        print("Пользователь с таким именем уже существует.")

def login_user(username, password):
    cursor.execute('SELECT id, balance FROM users WHERE username = ? AND password = ?', (username, password))
    user = cursor.fetchone()
    if user:
        return user
    else:
        print("Неправильное имя пользователя или пароль.")
        return None

# Получение котировок акций
def get_stock_price(symbol):
    stock = yf.Ticker(symbol)
    data = stock.history(period="1d")
    return data['Close'][0]

# Покупка акций
def buy_stock(user_id, symbol, quantity):
    price = get_stock_price(symbol)
    total_cost = price * quantity

    # Проверяем баланс пользователя
    cursor.execute('SELECT balance FROM users WHERE id = ?', (user_id,))
    balance = cursor.fetchone()[0]
    
    if total_cost > balance:
        print(f"Недостаточно средств! Ваш баланс: {balance:.2f}, требуется: {total_cost:.2f}")
    else:
        # Обновляем баланс и сохраняем сделку
        cursor.execute('UPDATE users SET balance = balance - ? WHERE id = ?', (total_cost, user_id))
        cursor.execute('INSERT INTO trades (user_id, stock_symbol, price, quantity, trade_type) VALUES (?, ?, ?, ?, ?)', 
                       (user_id, symbol, price, quantity, "buy"))
        conn.commit()
        print(f"Успешно куплено {quantity} акций {symbol} по цене {price:.2f}. Общая стоимость: {total_cost:.2f}")

# Продажа акций
def sell_stock(user_id, symbol, quantity):
    price = get_stock_price(symbol)
    total_income = price * quantity

    # Обновляем баланс и сохраняем сделку
    cursor.execute('UPDATE users SET balance = balance + ? WHERE id = ?', (total_income, user_id))
    cursor.execute('INSERT INTO trades (user_id, stock_symbol, price, quantity, trade_type) VALUES (?, ?, ?, ?, ?)', 
                   (user_id, symbol, price, quantity, "sell"))
    conn.commit()
    print(f"Успешно продано {quantity} акций {symbol} по цене {price:.2f}. Общий доход: {total_income:.2f}")

# Показать баланс и историю сделок
def show_portfolio(user_id):
    cursor.execute('SELECT balance FROM users WHERE id = ?', (user_id,))
    balance = cursor.fetchone()[0]
    print(f"Текущий баланс: {balance:.2f}")

    print("История сделок:")
    cursor.execute('SELECT stock_symbol, price, quantity, trade_type FROM trades WHERE user_id = ?', (user_id,))
    trades = cursor.fetchall()
    for trade in trades:
        print(f"{trade[3].capitalize()} - Акция: {trade[0]}, Цена: {trade[1]:.2f}, Количество: {trade[2]}")

# Главная функция
def main():
    print("Добро пожаловать в трейдинговую платформу!")
    
    while True:
        choice = input("1: Регистрация, 2: Вход, 3: Выход: ")

        if choice == '1':
            username = input("Введите имя пользователя: ")
            password = getpass("Введите пароль: ")
            register_user(username, password)
        
        elif choice == '2':
            username = input("Введите имя пользователя: ")
            password = getpass("Введите пароль: ")
            user = login_user(username, password)
            if user:
                user_id, balance = user
                print(f"Добро пожаловать, {username}! Ваш баланс: {balance:.2f}")

                while True:
                    action = input("1: Покупка, 2: Продажа, 3: Портфель, 4: Выйти: ")
                    if action == '1':
                        symbol = input("Введите тикер акции: ")
                        quantity = float(input("Количество: "))
                        buy_stock(user_id, symbol, quantity)
                    elif action == '2':
                        symbol = input("Введите тикер акции: ")
                        quantity = float(input("Количество: "))
                        sell_stock(user_id, symbol, quantity)
                    elif action == '3':
                        show_portfolio(user_id)
                    elif action == '4':
                        break
                    else:
                        print("Неправильный выбор.")
        
        elif choice == '3':
            print("Выход из программы.")
            break
        else:
            print("Неправильный выбор.")

if __name__ == "__main__":
    main()