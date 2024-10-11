import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

MIN_PRICE = 0.1
MAX_PRICE = 62000
VOLATILITY = 8
MAX_MARKET_HISTORY = 1000

old_price = 1000
market_data = []

def get_random_float():
    return np.random.random()

def update_fake_market(): 
    global old_price, market_data
    
    change_percent = 2 * VOLATILITY * (get_random_float() - 0.5)
    change_amount = old_price * change_percent / 100
    new_price = old_price + change_amount
    
    if new_price < MIN_PRICE:
        new_price += abs(change_amount) * 2
    elif new_price > MAX_PRICE:
        new_price -= abs(change_amount) * 2
    
    if len(market_data) == 0:
        market_data.append(old_price)
    market_data.append(new_price)
    
    if len(market_data) > MAX_MARKET_HISTORY:
        market_data.pop(0)
    
    old_price = new_price

# Generate fake market data
for _ in range(5000):
    update_fake_market()

# Convert market data to numpy array for analysis
market_data = np.array(market_data)

# Smoothing using a moving average
window_size = 10
smoothed_data = np.convolve(market_data, np.ones(window_size)/window_size, mode='valid')

# Prepare data for derivative
derivative_smoothed_data = np.gradient(smoothed_data)

# Smoothing the derivative
smoothed_derivative_data = np.convolve(derivative_smoothed_data, np.ones(window_size)/window_size, mode='valid')

# Identify zero crossings
zero_crossings = []
for i in range(1, len(smoothed_derivative_data)):
    if (smoothed_derivative_data[i-1] < 0 and smoothed_derivative_data[i] >= 0) or \
       (smoothed_derivative_data[i-1] > 0 and smoothed_derivative_data[i] <= 0):
        zero_crossings.append(i)

# Prepare data for prediction
X = np.array(range(len(market_data))).reshape(-1, 1)
y = market_data
model = LinearRegression()
model.fit(X, y)
predictions = model.predict(X)

# Plotting the results
plt.figure(figsize=(14, 10))

# Original market data plot
plt.subplot(7, 1, 1)
plt.plot(market_data, label='Fake Market Prices', color='blue')
plt.title('Fake Stock Market Prices')
plt.xlabel('Iterations')
plt.ylabel('Price')
plt.legend()

# Smoothed data plot
plt.subplot(7, 1, 2)
plt.plot(smoothed_data, label='Smoothed Prices', color='orange')
plt.title('Smoothed Fake Stock Market Prices')
plt.xlabel('Iterations (Smoothed)')
plt.ylabel('Price')
plt.legend()

# Heavy smoothed data plot
plt.subplot(7, 1, 3)
plt.plot(np.convolve(market_data, np.ones(50)/50, mode='valid'), label='Heavy Smoothed Prices', color='green')
plt.title('Heavy Smoothed Fake Stock Market Prices')
plt.xlabel('Iterations (Heavy Smoothed)')
plt.ylabel('Price')
plt.legend()

# Predictions plot
plt.subplot(7, 1, 4)
plt.plot(market_data, label='Fake Market Prices', color='blue', alpha=0.5)
plt.plot(predictions, label='Predicted Prices', color='red')
plt.title('Predicted Prices vs Actual Prices')
plt.xlabel('Iterations')
plt.ylabel('Price')
plt.legend()

# Derivative plot
plt.subplot(7, 1, 5)
plt.plot(derivative_smoothed_data, label='Derivative of Smoothed Prices', color='purple')
plt.plot([0, len(derivative_smoothed_data) - 1], [0, 0], label='Zero', color='black')
plt.title('Derivative of Smoothed Prices')
plt.xlabel('Iterations (Smoothed)')
plt.ylabel('Change in Price')
plt.legend()

# Smoothed Derivative plot
plt.subplot(7, 1, 6)
plt.plot(smoothed_derivative_data, label='Smoothed Derivative of Smoothed Prices', color='purple')
plt.plot([0, len(smoothed_derivative_data) - 1], [0, 0], label='Zero', color='black')
plt.title('Smoothed Derivative of Prices')
plt.xlabel('Iterations (Smoothed)')
plt.ylabel('Change in Price')
plt.legend()

# Zero Crossing Plot
plt.subplot(7, 1, 7)
zero_cross_prices = market_data[zero_crossings]
plt.plot(zero_crossings, zero_cross_prices, 'ro', label='Zero Crossings', markersize=5)
plt.plot(market_data, label='Fake Market Prices', color='blue', alpha=0.5)
plt.title('Zero Crossings of Derivative')
plt.xlabel('Iterations')
plt.ylabel('Price')
plt.legend()

plt.tight_layout()
plt.show()
