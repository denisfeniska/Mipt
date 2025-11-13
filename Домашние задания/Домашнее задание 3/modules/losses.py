import numpy as np


class BaseLoss:
    """
    Base class for loss function.
    """

    def func(self, X, y, w):
        """
        Get loss function value at w.
        """
        raise NotImplementedError('Func oracle is not implemented.')

    def grad(self, X, y, w):
        """
        Get loss function gradient value at w.
        """
        raise NotImplementedError('Grad oracle is not implemented.')


class LinearLoss(BaseLoss):
    """
    Loss function for linear regression.
    It should support l2 regularization.
    """

    def __init__(self, l2_coef):
        """
        Parameters
        ----------
        l2_coef - l2 regularization coefficient
        """
        self.l2_coef = l2_coef

    def func(self, X, y, w):
        """
        Get loss function value for data X, target y and coefficient w.

        Parameters
        ----------
        X : scipy.sparse.csr_matrix or numpy.ndarray
        y : 1d numpy.ndarray
        w : 1d numpy.ndarray

        Returns
        -------
        : float
        """
        N = X.shape[0]
        MSE = np.linalg.norm(X.dot(w) - y, ord=2)
        w_norm = np.linalg.norm(w[1:], ord=2)
        return 1 / N * (MSE ** 2) + self.l2_coef * (w_norm ** 2)


    def grad(self, X, y, w):
        """
        Get loss function gradient for data X, target y and coefficient w.

        Parameters
        ----------
        X : scipy.sparse.csr_matrix or numpy.ndarray
        y : 1d numpy.ndarray
        w : 1d numpy.ndarray
        Returns
        -------
        : 1d numpy.ndarray
        """
        N = X.shape[0]
        l2_grad = 2 * self.l2_coef * w
        l2_grad[0] = 0
        return 2 / N * X.T.dot(X.dot(w) - y) + l2_grad
