from . import Vector

class AABB:
    def __init__(self,min:Vector,max:Vector):
        self.min = min
        self.max = max

    def isOverlap(self,targetPoint:Vector)->bool:
        """Checks whether a target point is within the AABB box."""
        d1x = targetPoint.min.x - self.max.x
        d1y = targetPoint.min.y - self.max.y
        d2x = self.min.x - targetPoint.max.x
        d2y = self.min.y - targetPoint.max.y

        if (d1x > 0) or (d1y > 0):
            return False
        
        if (d2x > 0) or (d2y > 0):
            return False
        
        return True

# Handles collision calculation

def findColliders(target, searchList):
    """Given a target and a searchList, find all objects in searchList that collide with target using just a bounding box."""

    # Get the bounding box of the target

    # for each item in searchList
    #   for each corner of the current item, is it between targetmin and targetmax points
    #       if yes - > add to list if no, keep looking
