"""Class to store cube's positional data"""

class Cube():
    def __init__(self, json = None):
        self._top = 0
        self._bottom = 0
        self._front = 0 
        self._back = 0 
        self._left = 0
        self._right = 0
        self._rota_x = 0
        self._rota_y = 0
        self._rota_z = 0
        self.init_json(json)

    def init_json(self, json):
        """Reads the JSON data from the sensors and adujsts the 
        data of the cube according to it.
        
        Args:
            json (dict): JSON dict containing the sensors data.
        """
        if json is None:
            return
        for data in json:
            match data:
                case "Top":
                    self._top = int(json[data])
                case "Bottom":
                    self._bottom = int(json[data])
                case "Right":
                    self._right = int(json[data])
                case "Left":
                    self._left = int(json[data])
                case "Front":
                    self._front = int(json[data])
                case "Back":
                    self._back = int(json[data])
                case "X":
                    self._x = float(json[data])
                case "Y":
                    self._y = float(json[data])
                case "Z":
                    self._z = float(json[data])

    def display(self):
        """Prints the cube's data."""
        print(f"## Cube at : {self}\nTop \t: {self._top}cm\nBottom \t: {self._bottom}cm")
        print(f"Front \t: {self._front}cm\nBack \t: {self._back}cm\nLeft \t: {self._left}cm")
        print(f"Right \t: {self._right}cm\n## Gyroscope Data :")
        print(f"x : {self._rota_x}, y : {self._rota_y}, z = {self.rota_z}")

    @property
    def top(self):
        return self._top

    @top.setter
    def top(self, value):
        self._top = value

    @property
    def bottom(self):
        return self._bottom

    @bottom.setter
    def bottom(self, value):
        self._bottom = value

    @property
    def front(self):
        return self._front

    @front.setter
    def front(self, value):
        self._front = value

    @property
    def back(self):
        return self._back

    @back.setter
    def back(self, value):
        self._back = value

    @property
    def left(self):
        return self._left

    @left.setter
    def left(self, value):
        self._left = value

    @property
    def right(self):
        return self._right

    @right.setter
    def right(self, value):
        self._right = value

    @property
    def rota_x(self):
        return self._rota_x

    @rota_x.setter
    def rota_x(self, value):
        self._rota_x = value

    @property
    def rota_y(self):
        return self._rota_y

    @rota_y.setter
    def rota_y(self, value):
        self._rota_y = value

    @property
    def rota_z(self):
        return self._rota_z

    @rota_z.setter
    def rota_z(self, value):
        self._rota_z = value
