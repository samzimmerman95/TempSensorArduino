import numpy as np
import matplotlib.pyplot as plt

times = []

with open('backup.txt', 'r') as backup:
    lines = backup.readlines()
    for line in lines:
        l = line.strip()[1:11]
        n = [int(s) for s in l.split() if s.isdigit()]
        if len(n) > 0 and n[0] > 160000000:
            times.append(n[0])

times.sort()
npTimes = np.array(times)
# filterArr = npTimes > 1630124390
filterArr = npTimes > 1631059390
recentTimes = npTimes[filterArr]

diff = np.diff(recentTimes)

retries = diff / 1336

t = 1
print("Count:", len(retries))
print("Median attemps:", "{:.2f}".format(np.median(retries)))
print("Min:", "{:.2f}".format(np.min(retries)))
print("Max:", "{:.2f}".format(np.max(retries)))
hist, bins = np.histogram(retries, bins=[i+0.5 for i in range(12)])
print(hist)
print("First attempt success rate:",
      "{:.2f} %".format(hist[0]/len(retries)*100))

plt.hist(retries, bins=[i+0.5 for i in range(12)])
plt.title("Number of retries histogram")
plt.show()

plt.plot(retries)
plt.title("Number of retries over time")
plt.show()

# recentTimes = recentTimes[1:]
# d = {}
# for i in range(len(recentTimes)):
#     hour = ((recentTimes[i]-3600*7) % (3600*24)) // 3600
#     if hour in d:
#         d[hour] = np.append(d[hour], retries[i])
#     else:
#         d[hour] = np.array([retries[i]])

# for h in d:
#     d[h] = np.median(d[h])

# x = list(d.keys())
# h = list(d.values())

# plt.bar(x, h)
# plt.title("Median # of attempts at each hour")
# plt.show()


# with open('times.txt', 'w') as time:
#     time.writelines(times)
