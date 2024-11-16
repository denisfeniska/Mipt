import pygame
import math
from typing import List, Tuple, Optional
from constants import (
    WHITE, GREEN, RED, BLACK, BROWN, BLUE, YELLOW, PURPLE, CYAN,
    FPS, FRICTION, MIN_SPEED_THRESHOLD, WIDTH, HEIGHT,
    TABLE_X, TABLE_Y, TABLE_WIDTH, TABLE_HEIGHT, HOLE_RADIUS
)

# Инициализация Pygame
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Бильярд")


class Ball:
    def __init__(self, x: float, y: float, radius: int, color: Tuple[int, int, int]) -> None:
        """
        Инициализация объекта шара.
        :param x: Позиция по X.
        :param y: Позиция по Y.
        :param radius: Радиус шара.
        :param color: Цвет шара (RGB).
        """
        self.x: float = x
        self.y: float = y
        self.radius: int = radius
        self.color: Tuple[int, int, int] = color
        self.vx: float = 0
        self.vy: float = 0
        self.in_play: bool = True

    def draw(self, screen: pygame.Surface) -> None:
        """
        Отрисовка шара на экране.
        :param screen: Поверхность для отрисовки.
        """
        if self.in_play:
            pygame.draw.circle(screen, self.color, (int(self.x), int(self.y)), self.radius)

    def move(self) -> None:
        """
        Перемещение шара и обработка столкновений с границами стола.
        """
        if self.in_play:
            self.x += self.vx
            self.y += self.vy

            # Применяем трение
            self.vx *= FRICTION
            self.vy *= FRICTION

            # Проверяем столкновения с границами стола
            if self.x - self.radius < TABLE_X or self.x + self.radius > TABLE_X + TABLE_WIDTH:
                self.vx = -self.vx
            if self.y - self.radius < TABLE_Y or self.y + self.radius > TABLE_Y + TABLE_HEIGHT:
                self.vy = -self.vy

            # Останавливаем шар, если скорость очень мала
            if abs(self.vx) < MIN_SPEED_THRESHOLD:
                self.vx = 0
            if abs(self.vy) < MIN_SPEED_THRESHOLD:
                self.vy = 0

    def hit(self, force: float, angle: float) -> None:
        """
        Применение удара по шару.
        :param force: Сила удара.
        :param angle: Угол удара (в радианах).
        """
        if self.in_play:
            self.vx = force * math.cos(angle)
            self.vy = force * math.sin(angle)

    def check_hole(self, holes: List[Tuple[int, int]]) -> None:
        """
        Проверка, попал ли шар в лузу.
        :param holes: Список координат луз.
        """
        for hole in holes:
            distance = math.hypot(self.x - hole[0], self.y - hole[1])
            if distance < HOLE_RADIUS:
                self.in_play = False
                break

    def check_collision(self, other: 'Ball') -> None:
        """
        Проверка и обработка столкновения с другим шаром.
        :param other: Другой шар.
        """
        if not self.in_play or not other.in_play:
            return

        dx = other.x - self.x
        dy = other.y - self.y
        distance = math.hypot(dx, dy)

        if distance < self.radius + other.radius:
            angle = math.atan2(dy, dx)

            # Начальные скорости
            v1 = math.hypot(self.vx, self.vy)
            v2 = math.hypot(other.vx, other.vy)

            # Направления движения
            dir1 = math.atan2(self.vy, self.vx)
            dir2 = math.atan2(other.vy, other.vx)

            # Новые скорости после столкновения
            new_vx1 = v2 * math.cos(dir2 - angle)
            new_vy1 = v2 * math.sin(dir2 - angle)
            new_vx2 = v1 * math.cos(dir1 - angle)
            new_vy2 = v1 * math.sin(dir1 - angle)

            self.vx = new_vx1 * math.cos(angle) - new_vy1 * math.sin(angle)
            self.vy = new_vx1 * math.sin(angle) + new_vy1 * math.cos(angle)

            other.vx = new_vx2 * math.cos(angle) - new_vy2 * math.sin(angle)
            other.vy = new_vx2 * math.sin(angle) + new_vy2 * math.cos(angle)


class Game:
    def __init__(self) -> None:
        """
        Инициализация игры, создание шаров и луз.
        """
        self.balls: List[Ball] = [
            Ball(400, 200, 15, RED),
            Ball(450, 250, 15, WHITE),
            Ball(500, 150, 15, WHITE),
            Ball(350, 150, 15, BLUE),
            Ball(300, 250, 15, YELLOW),
            Ball(550, 250, 15, PURPLE),
            Ball(450, 100, 15, CYAN),
        ]
        self.holes: List[Tuple[int, int]] = [
            (TABLE_X, TABLE_Y),
            (TABLE_X + TABLE_WIDTH, TABLE_Y),
            (TABLE_X, TABLE_Y + TABLE_HEIGHT),
            (TABLE_X + TABLE_WIDTH, TABLE_Y + TABLE_HEIGHT),
            (TABLE_X + TABLE_WIDTH // 2, TABLE_Y),
            (TABLE_X + TABLE_WIDTH // 2, TABLE_Y + TABLE_HEIGHT),
        ]
        self.running: bool = True

    def draw_table(self) -> None:
        """
        Отрисовка стола и луз.
        """
        pygame.draw.rect(screen, GREEN, (TABLE_X, TABLE_Y, TABLE_WIDTH, TABLE_HEIGHT))
        for hole in self.holes:
            pygame.draw.circle(screen, BLACK, hole, HOLE_RADIUS)

    def check_game_over(self) -> bool:
        """
        Проверка, остались ли шары на столе.
        :return: True, если все шары попали в лузы.
        """
        return all(not ball.in_play for ball in self.balls)

    def draw_text(self, text: str, font_size: int, color: Tuple[int, int, int], position: Tuple[int, int]) -> None:
        """
        Отображение текста на экране.
        :param text: Текст для отображения.
        :param font_size: Размер шрифта.
        :param color: Цвет текста (RGB).
        :param position: Позиция текста на экране.
        """
        font = pygame.font.SysFont(None, font_size)
        text_surface = font.render(text, True, color)
        screen.blit(text_surface, position)

    def run(self) -> None:
        """
        Основной цикл игры.
        """
        clock = pygame.time.Clock()
        selected_ball: Optional[Ball] = None

        while self.running:
            screen.fill(BROWN)
            self.draw_table()

            if self.check_game_over():
                self.draw_text("Игра закончилась", 60, WHITE, (250, 180))
            else:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        self.running = False
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        for ball in self.balls:
                            distance = math.hypot(ball.x - event.pos[0], ball.y - event.pos[1])
                            if distance < ball.radius:
                                selected_ball = ball
                    if event.type == pygame.MOUSEBUTTONUP:
                        if selected_ball:
                            mouse_x, mouse_y = pygame.mouse.get_pos()
                            dx = mouse_x - selected_ball.x
                            dy = mouse_y - selected_ball.y
                            angle = math.atan2(dy, dx)
                            force = min(math.hypot(dx, dy) / 10, 10)
                            selected_ball.hit(force, angle)
                            selected_ball = None

                for i, ball in enumerate(self.balls):
                    ball.move()
                    ball.check_hole(self.holes)
                    for other_ball in self.balls[i + 1:]:
                        ball.check_collision(other_ball)
                    ball.draw(screen)

            pygame.display.flip()
            clock.tick(FPS)

        pygame.quit()


if __name__ == "__main__":
    game = Game()
    game.run()
