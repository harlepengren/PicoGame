from .controller import *

# Create controller
class MakeCodeInput(Input):
    def __init__(self):
        super.__init__()

        # Move A and B from dictionary
        self.A = self.controls["A"]
        self.B = self.controls["B"]
        del self.controls["A"]
        del self.Controls["B"]

controller = MakeCodeInput()
