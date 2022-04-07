import cartesianMesher2d
import matplotlib.pyplot as plt


polyStructure = [
    # first element with 2 holes
	[
		[[5, 0], [10, 5], [5, 10], [0, 5]],
		[
			[[5, 0.5], [6, 1.5], [4, 1.5]],
			[[7, 3], [7, 7], [3, 7], [3, 3]]
		]
	],
    # second element with 1 hole
	[
		[[3.5,	3.5], [6.5, 3.5], [5, 6.5]],
		[
			[[4, 4], [6, 4], [5, 5]]
		]
	],
    # third element with no holes
	[
		[[5.5, 6], [6.5, 5], [6.5, 6.5]]
	]
]
rects = cartesianMesher2d.meshMore(polyStructure, 0.05)
print(rects)


# plot polygonStructure
for poly in polyStructure:
	face = poly.pop(0)
	face.append(face[0])
	xs,ys = zip(*face)
	plt.plot(xs,ys, color="b")
	if not poly:
		continue
	holes = poly.pop(0)
	for hole in holes:
		hole.append(hole[0])
		xs,ys = zip(*hole)
		plt.plot(xs,ys, color="g")
		
# plot rects
for rect in rects:
	rect.append(rect[0])
	xs,ys = zip(*rect)
	plt.plot(xs,ys, color="r")

plt.show()
