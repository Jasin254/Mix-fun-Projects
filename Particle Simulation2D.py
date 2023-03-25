import math

class Particle:
    def __init__(self, x, y, vx, vy, mass, radius):
        self.x = x        # x-coordinate
        self.y = y        # y-coordinate
        self.vx = vx      # x-velocity
        self.vy = vy      # y-velocity
        self.mass = mass  # mass
        self.radius = radius  # radius

    def move(self, dt):
        self.x += self.vx * dt
        self.y += self.vy * dt

    def apply_force(self, fx, fy, dt):
        self.vx += fx * dt / self.mass
        self.vy += fy * dt / self.mass

    def distance_to(self, other):
        dx = self.x - other.x
        dy = self.y - other.y
        return math.sqrt(dx*dx + dy*dy)

    def collide(self, other):
        distance = self.distance_to(other)
        if distance < self.radius + other.radius:
            # calculate new velocities
            nx = (self.x - other.x) / distance
            ny = (self.y - other.y) / distance
            dvx = self.vx - other.vx
            dvy = self.vy - other.vy
            dot_product = dvx * nx + dvy * ny
            fx = nx * dot_product
            fy = ny * dot_product
            self.vx -= fx / self.mass
            self.vy -= fy / self.mass
            other.vx += fx / other.mass
            other.vy += fy / other.mass

# set up initial conditions
p1 = Particle(x=0.0, y=0.0, vx=1.0, vy=1.0, mass=1.0, radius=0.1)
p2 = Particle(x=1.0, y=0.0, vx=0.0, vy=0.0, mass=1.0, radius=0.1)

# simulation parameters
dt = 0.01  # time step
t_end = 10.0  # end time

# simulation loop
t = 0.0
while t < t_end:
    # apply forces
    fx = 0.0
    fy = 0.0
    distance = p1.distance_to(p2)
    if distance < 2.0:
        fx = -0.1 * (p1.x - p2.x)
        fy = -0.1 * (p1.y - p2.y)
    p1.apply_force(fx, fy, dt)
    p2.apply_force(-fx, -fy, dt)

    # move particles
    p1.move(dt)
    p2.move(dt)

    # handle collisions
    p1.collide(p2)

    t += dt
