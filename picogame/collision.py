from . import Vector

# Handles collision calculation

def findColliders(target, searchList):
    """Given a target and a searchList, find all objects in searchList that collide with target using just a bounding box."""

    # Get the bounding box of the target
