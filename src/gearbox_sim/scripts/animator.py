#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import math


class GearboxAnimator(Node):
    def __init__(self):
        super().__init__('gearbox_animator')
        # Публикуем состояния (углы) для RViz
        self.publisher_ = self.create_publisher(JointState, 'joint_states', 10)

        # Таймер: 30 кадров в секунду
        self.timer = self.create_timer(1.0 / 30.0, self.timer_callback)

        # Текущий угол водила 
        self.carrier_angle = 0.0

        self.carrier_step = 0.01

        # Z_ring = 60, Z_sun = 12, Z_planet = 24
        self.ring_teeth = 60.0
        self.sun_teeth = 12.0
        self.planet_teeth = 24.0

        # Три сателлита через 120 градусов.
        # Для соседних сателлитов добавляем фазовый сдвиг по зубьям,
        # чтобы в стартовом положении зацепление выглядело корректно.
        planet_tooth_pitch = math.tau / self.planet_teeth
        half_tooth_pitch = 0.5 * planet_tooth_pitch
        self.planet_phase_offsets = [
            half_tooth_pitch,
            half_tooth_pitch - 4.0 * planet_tooth_pitch,
            half_tooth_pitch - 8.0 * planet_tooth_pitch,
        ]

    def timer_callback(self):
        msg = JointState()
        msg.header.stamp = self.get_clock().now().to_msg()

        # Имена как в gearbox.urdf
        msg.name = [
            'carrier_joint',
            'sun_joint',
            'planet_1_joint',
            'planet_2_joint',
            'planet_3_joint',
        ]

        # Шаг вращения водила (задаем общую скорость механизма)
        self.carrier_angle += self.carrier_step

        # --- Планетарка---
        # При неподвижной короне: w_sun = w_carrier * (1 + Z_ring / Z_sun)
        sun_angle = (1.0 + self.ring_teeth / self.sun_teeth) * self.carrier_angle

        # URDF шарнир сателлита задан относительно водила,
        # поэтому публикуем относительный угол: (w_planet - w_carrier).
        planet_relative_angle = -(self.ring_teeth / self.planet_teeth) * self.carrier_angle
        planet_angles = [
            planet_relative_angle + offset for offset in self.planet_phase_offsets
        ]

        # Упаковываем углы и отправляем
        msg.position = [self.carrier_angle, sun_angle, *planet_angles]
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = GearboxAnimator()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass  # Закрытие без спама
    finally:
        node.destroy_node()
        # Проверка чтобы избежать ошибки 
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()
