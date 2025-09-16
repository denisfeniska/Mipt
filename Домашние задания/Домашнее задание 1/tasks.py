import numpy as np


# 2 points
def euclidean_distance(X, Y) -> np.ndarray:
    """
    Compute element wise euclidean distance.

    Parameters
    ----------
    X: np.ndarray of size M * K
    Y: np.ndarray of size N * K

    Returns
    -------
    np.ndarray of size M * N
        Each element of which is the Euclidean distance between the corresponding pair of vectors from the arrays X and Y
    """
    raise NotImplementedError()


# 2 points
def cosine_distance(X, Y) -> np.ndarray:
    """
    Compute element wise cosine distance.

    Parameters
    ----------
    X: np.ndarray of size M * K
    Y: np.ndarray of size N * K

    Returns
    -------
    np.ndarray of size M * N
        Each element of which is the cosine distance between the corresponding pair of vectors from the arrays X and Y
    """
    raise NotImplementedError()


# 1 point
def manhattan_distance(X, Y) -> np.ndarray:
    """
    Compute element wise manhattan distance.

    Parameters
    ----------
    X: np.ndarray of size M * K
    Y: np.ndarray of size N * K

    Returns
    -------
    np.ndarray of size M * N
        Each element of which is the manhattan distance between the corresponding pair of vectors from the arrays X and Y
    """
    raise NotImplementedError()