from typing import cast

from core import Order, make_processor


def render_report(result: dict[str, object]) -> None:
    orders = cast(list[Order], result.get("orders", []))

    print("=== ЗВІТ З ОБРОБКИ ЗАМОВЛЕНЬ ===")
    for o in orders:
        print(f"Оброблено замовлення #{o['id']} | Підсумкова сума: {o['total']:.2f}")

    print("-" * 30)
    print(f"Кількість валідних замовлень: {result['count']}")

    revenue = cast(float, result.get("revenue", 0.0))
    print(f"Загальний дохід (Revenue): {revenue:.2f}")


def main() -> None:
    sample_orders: list[Order] = [
        {
            "id": 1,
            "items": [{"price": 50.0, "qty": 2}, {"price": 10.0, "qty": 1}],
            "paid": True,
        },
        {
            "id": 2,
            "items": [{"price": 20.0, "qty": 1}],
            "paid": False,
        },
        {
            "id": 3,
            "items": [{"price": 30.0, "qty": 2}],
            "paid": True,
        },
        {"id": 4, "items": [{"price": 200.0, "qty": 1}], "paid": True},  # Сума: 200
    ]

    accept_policy = lambda s: s >= 100
    discount_policy = lambda s: s * 0.9
    tax_policy = lambda s: s * 1.2

    processor = make_processor(
        accept=accept_policy, apply_discount=discount_policy, apply_tax=tax_policy
    )

    result = processor(sample_orders)

    render_report(result)


if __name__ == "__main__":
    main()
