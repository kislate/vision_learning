import numpy as np
from filterpy.kalman import KalmanFilter
import matplotlib.pyplot as plt

# 1. 定义状态转移矩阵、观测矩阵、噪声
dt = 1  # 时间间隔

# 2. 初始化卡尔曼滤波器
kf = KalmanFilter(dim_x=4, dim_z=2)  # 4 states (x, y, vx, vy), 2 measurements (x, y)
kf.F = np.array([[1, 0, dt, 0],
                   [0, 1, 0, dt],
                   [0, 0, 1, 0],
                   [0, 0, 0, 1]])  # State transition matrix
kf.H = np.array([[1, 0, 0, 0],
                   [0, 1, 0, 0]])  # Measurement function
kf.P *= 0.1  # Initial covariance matrix
kf.R = np.array([[5, 0],
                   [0, 5]])  # Measurement noise covariance
kf.Q = np.array([[0.1, 0, 0.1, 0],
                   [0, 0.1, 0, 0.1],
                   [0.1, 0, 0.1, 0],
                   [0, 0.1, 0, 0.1]])  # Process noise covariance

# 3. 生成模拟数据
true_x = np.arange(0, 100, 1)
true_y = np.arange(0, 100, 1)
measurements = np.vstack((true_x + np.random.randn(100) * np.sqrt(5),
                          true_y + np.random.randn(100) * np.sqrt(5)))

# 4. 运行卡尔曼滤波器
kf.x = np.array([measurements[0, 0], measurements[1, 0], 0, 0])  # Initial state
mu, S, _, _ = kf.batch_filter(measurements.T)  # run filter on measurements, output is mu (state mean), S (covariance matrix)

# 5. 可视化结果
plt.plot(measurements[0], measurements[1], 'r+', label='Measurement')
plt.plot(true_x, true_y, 'g-', label='Truth')
plt.plot(mu[:, 0], mu[:, 1], 'b-', label='Kalman Estimate')
plt.legend()
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Kalman Filter Tracking')
plt.show()