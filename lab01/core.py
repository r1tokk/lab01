from collections.abc import Callable, Iterable
from typing import TypedDict


class Item(TypedDict):
    price: float
    qty: int


class Order(TypedDict, total=False):
    id: int
    items: list[Item]
    paid: bool
    total: float


FilterFn = Callable[[float], bool]
DiscountFn = Callable[[float], float]
TaxFn = Callable[[float], float]
ProcessorFn = Callable[[Iterable[Order]], dict[str, object]]


def order_subtotal(order: Order) -> float:
    return sum(it["price"] * it["qty"] for it in order.get("items", []))


def with_total(order: Order, total: float) -> Order:
    return {**order, "total": total}


def make_processor(
    accept: FilterFn,
    apply_discount: DiscountFn,
    apply_tax: TaxFn,
) -> ProcessorFn:
    def process(orders: Iterable[Order]) -> dict[str, object]:
        qualified = []
        revenue = 0.0

        for o in orders:
            if not o.get("paid"):
                continue

            subtotal = order_subtotal(o)

            if not accept(subtotal):
                continue

            total = apply_tax(apply_discount(subtotal))

            new_order = with_total(o, total)
            qualified.append(new_order)
            revenue += total

        return {"count": len(qualified), "revenue": revenue, "orders": qualified}

    return process
