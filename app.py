import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression

# 创建一个简单的数据集
X = np.array([[1], [2], [3], [4], [5]])
y = np.array([1, 3, 2, 3, 5])

# 创建线性回归模型
model = LinearRegression()
model.fit(X, y)

# 进行预测并输出
predictions = model.predict([[6]])
print("Prediction for input 6:", predictions)

