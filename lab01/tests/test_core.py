from copy import deepcopy

import pytest

from core import Order, make_processor


@pytest.fixture
def sample_orders() -> list[Order]:
    return [
        {"id": 1, "items": [{"price": 100.0, "qty": 1}], "paid": True},
        {"id": 2, "items": [{"price": 50.0, "qty": 2}], "paid": True},
    ]


def test_referential_transparency(sample_orders: list[Order]) -> None:
    processor = make_processor(
        accept=lambda s: s >= 0,
        apply_discount=lambda s: s * 0.9,
        apply_tax=lambda s: s * 1.2,
    )

    r1 = processor(sample_orders)
    r2 = processor(sample_orders)

    assert r1 == r2


def test_no_mutation(sample_orders: list[Order]) -> None:
    original = deepcopy(sample_orders)
    processor = make_processor(
        accept=lambda s: s >= 0, apply_discount=lambda s: s, apply_tax=lambda s: s
    )

    processor(sample_orders)

    assert sample_orders == original


def test_callable_policies(sample_orders: list[Order]) -> None:
    processor = make_processor(
        accept=lambda s: s >= 100,  # Тільки суми >= 100
        apply_discount=lambda s: s - 10,  # Фіксована знижка 10
        apply_tax=lambda s: s * 1.1,  # Податок 10%
    )

    result = processor(sample_orders)

    assert result["count"] == 2

    orders = result["orders"]
    assert isinstance(orders, list)

    assert abs(orders[0]["total"] - 99.0) < 0.001

    assert result["revenue"] == pytest.approx(198.0)
