import numpy as np
import time


class LinearModel:
    def __init__(
        self,
        loss_function,
        batch_size=None,
        step_alpha=1,
        step_beta=0, 
        tolerance=1e-5,
        max_iter=1000,
        random_seed=153,
        **kwargs
    ):
        """
        Parameters
        ----------
        loss_function : BaseLoss inherited instance
            Loss function to use
        batch_size : int
        step_alpha : float
        step_beta : float
            step_alpha and step_beta define the learning rate behaviour
        tolerance : float
            Tolerace for stop criterio. CRITERIO: np.linalg.norm(current_w - previous_w) < tolerance
        max_iter : int
            Max amount of epoches in method.
        """
        self.loss_function = loss_function
        self.batch_size = batch_size
        self.step_alpha = step_alpha
        self.step_beta = step_beta
        self.tolerance = tolerance
        self.max_iter = max_iter
        self.random_seed = random_seed
        self.w_res = None

    def fit(self, X, y, w_0=None, trace=False, X_val=None, y_val=None):
        """

        Parameters
        ----------
        X : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix, training set.
        y : numpy.ndarray
            1d vector, target values.
        w_0 : numpy.ndarray
            1d vector for initial approximation for SGD method.
        trace : bool
            If True need to calculate metrics on each iteration.
        X_val : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix, validation set.
        y_val: numpy.ndarray
            1d vector, target values for validation set.

        Returns
        -------
        : dict
            Keys are 'time', 'func', 'func_val'.
            Each key correspond to list of metric values after each training epoch.
        """
        N = X.shape[0]
        D = X.shape[1]
        history = {'time': [], 'func': [], 'func_val': []} if trace else None
        w = w_0.copy() if w_0 is not None else np.zeros(D)
        w_prev = w.copy()
        batch_size_m = self.batch_size if self.batch_size is not None else N

        rng = np.random.default_rng(self.random_seed)
        
        for epoch in range(1, self.max_iter + 1):
            indexes = np.arange(N)
            rng.shuffle(indexes)

            time_start = time.time()

            for start in range(0, N, batch_size_m):
                stop = min(N, start + batch_size_m)
                batch_idx = indexes[start:stop]
                batch_X = X[batch_idx]
                batch_y = y[batch_idx]

                grad_coeff = self.step_alpha / (epoch ** self.step_beta)
                w = w - grad_coeff * self.loss_function.grad(batch_X, batch_y, w)

            time_stop = time.time()
            time_diff = time_stop - time_start
            if trace:
                history['time'].append(time_diff)
                history['func'].append(self.loss_function.func(X, y, w))
                if X_val is not None and y_val is not None:
                    history['func_val'].append(self.loss_function.func(X_val, y_val, w))
                else:
                    history['func_val'].append(None)
            if np.linalg.norm(w - w_prev) <= self.tolerance:
                break

            w_prev = w.copy()

        self.w_res = w.copy()
        return history if history else None


    def predict(self, X):
        """

        Parameters
        ----------
        X : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix, test set.

        Returns
        -------
        : numpy.ndarray
            answers on a test set
        """
        return X.dot(self.w_res)

    def get_weights(self):
        """
        Get model weights

        Returns
        -------
        : numpy.ndarray
            1d model weights vector.
        """
        return self.w_res

    def get_objective(self, X, y):
        """
        Get objective.

        Parameters
        ----------
        X : numpy.ndarray or scipy.sparse.csr_matrix
            2d matrix.
        y : numpy.ndarray
            1d vector, target values for X.

        Returns
        -------
        : float
        """
        return self.loss_function.func(X, y, self.w_res)
