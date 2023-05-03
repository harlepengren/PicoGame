from . import vector

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

def getAABB(target):
    """Given a sprite, return the AABB."""

    targetPosition = target.Position
    targetAABB = AABB(targetPosition, Vector(targetPosition + target.width, targetPosition + target.heigth))

    return targetAABB

def findColliders(target, searchList):
    """Given a target and a searchList, find all objects in searchList that collide with target using just a bounding box."""

    targetAABB = getAABB(target)

    collisionList = []
    # for each item in searchList
    for item in searchList:
        otherAABB = getAABB(item)
        
        if targetAABB.isOverlap(otherAABB):
            collisionList.append(item)
