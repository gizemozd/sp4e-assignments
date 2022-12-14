import argparse
import numpy as np


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('--xlim', action='store', type=float, default=[-1.0, 1.0], help="lower and upper bounds of x")
    parser.add_argument('--ylim', action='store', type=float, nargs='+', default=[-1.0, 1.0], help="lower and upper bounds of y")
    parser.add_argument('--size',  action='store', type=int, default=512, help="size of the grid")
    parser.add_argument('--radius',  action='store', type=float, default=0.5,help="radius of area f particles")
    parser.add_argument('-fname', action='store', default="heatDistribution.csv",help="file name")
    return parser.parse_args()


# heat distribution function
def heatDistribution(xlim, ylim, size, radius, fname):
    x_vals = np.linspace(xlim[0], xlim[1], size)
    y_vals = np.linspace(ylim[0], ylim[1], size)
    heat_vals = []
    for x in x_vals:
        for y in y_vals:
            r = x**2 + y**2
            if r < radius:
                heat_vals += [[x, y]]
            else:
                heat_vals += [[0, 0]]
    heat_vals = np.asarray(heat_vals)
    np.savetxt(fname, heat_vals, delimiter=',')
    return


if __name__ == "__main__":
    args = arg_parser()
    print(args)
    heatDistribution(xlim=args.xlim, ylim=args.ylim, size=args.size, radius=args.radius, fname=args.fname)
    print("heat distribution file is generated")
