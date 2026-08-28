class Robot:
    def __init__(self, width: int, height: int):
        self.w = width
        self.h = height
        self.perimeter = 2 * (width + height - 2)
        self.pos = 0
        self.has_moved = False

    def step(self, num: int) -> None:
        # Optimize steps by wrapping around the perimeter
        self.pos = (self.pos + num) % self.perimeter
        self.has_moved = True

    def getPos(self) -> list[int]:
        if self.pos == 0:
            return [0, 0]
        elif self.pos <= self.w - 1:
            # Bottom edge
            return [self.pos, 0]
        elif self.pos <= self.w + self.h - 2:
            # Right edge
            return [self.w - 1, self.pos - (self.w - 1)]
        elif self.pos <= 2 * self.w + self.h - 3:
            # Top edge
            return [(self.w - 1) - (self.pos - (self.w + self.h - 2)), self.h - 1]
        else:
            # Left edge
            return [0, (self.h - 1) - (self.pos - (2 * self.w + self.h - 3))]

    def getDir(self) -> str:
        if self.pos == 0:
            # If it hasn't moved, it faces East. If it looped back to origin, it faces South.
            return "South" if self.has_moved else "East"
        elif self.pos <= self.w - 1:
            return "East"
        elif self.pos <= self.w + self.h - 2:
            return "North"
        elif self.pos <= 2 * self.w + self.h - 3:
            return "West"
        else:
            return "South"