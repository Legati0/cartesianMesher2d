import cartesianMesher2d
import matplotlib.pyplot as plt


poly = [[0, 0], [0, 3], [2.5, 2.5], [3, 0]]
rects = cartesianMesher2d.mesh(poly, 0.01)
print(rects)


# plot poly
poly.append(poly[0])
xs,ys = zip(*poly)
plt.plot(xs,ys, color="b")

# plot rects
for rect in rects:
	rect.append(rect[0])
	xs,ys = zip(*rect)
	plt.plot(xs,ys, color="r")
	
plt.show()
