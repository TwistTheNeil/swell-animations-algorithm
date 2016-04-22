#include "hermite.cpp"
#include <gtest/gtest.h>

const double EPSILON = (double)1e-6;

TEST(hermite_create_pt, can_create) {
	pt *p = createPoint(1,2,3);
	ASSERT_EQ(1, p->x);
	ASSERT_EQ(2, p->y);
	ASSERT_EQ(3, p->z);
	free(p);

	p = createPoint(7.9, 2.3, 198.54);
	ASSERT_EQ(7.9, p->x);
	ASSERT_EQ(2.3, p->y);
	ASSERT_EQ(198.54, p->z);
	free(p);
}

TEST(hermite_add, can_add) {
	pt *p, *q, *r;
	p = createPoint(1, 2, 3);
	q = createPoint(7, 8, 9);
	r = add(p, q);
	ASSERT_EQ(8, p->x + q->x);
	ASSERT_EQ(10, p->y + q->y);
	ASSERT_EQ(12, p->z + q->z);
	free(p);
	free(q);
	free(r);

	p = createPoint(76.4, 2.44, 76.9);
	q = createPoint(12.8, 8.23, 9.1);
	r = add(p, q);
	ASSERT_EQ(89.2, p->x + q->x);
	ASSERT_EQ(10.67, p->y + q->y);
	ASSERT_EQ(86.0, p->z + q->z);
	free(p);
	free(q);
	free(r);
}

TEST(hermite_minus, can_subtract) {
	pt *p, *q, *r;
	p = createPoint(7, 8, 9);
	q = createPoint(1, 2, 3);
	r = minus(p, q);
	ASSERT_TRUE(fabs(6 - (p->x - q->x)) < EPSILON);
	ASSERT_TRUE(fabs(6 - (p->y - q->y)) < EPSILON);
	ASSERT_TRUE(fabs(6 - (p->z - q->z)) < EPSILON);
	free(p);
	free(q);
	free(r);

	p = createPoint(76.4, 2.44, 76.9);
	q = createPoint(12.8, 8.23, 9.1);
	r = minus(p, q);
	ASSERT_TRUE(fabs(63.6 - (p->x - q->x)) < EPSILON);
	ASSERT_TRUE(fabs(-5.79 - (p->y - q->y)) < EPSILON);
	ASSERT_TRUE(fabs(67.8 - (p->z - q->z)) < EPSILON);
	free(p);
	free(q);
	free(r);
}

TEST(hermite_mult, can_multiply) {
	pt *p, *q, *r;
	p = createPoint(7, 8, 9);
	q = createPoint(1, 2, 3);
	r = mult(p, q);
	ASSERT_TRUE(fabs(7 - (r->x)) < EPSILON);
	ASSERT_TRUE(fabs(16 - (r->y)) < EPSILON);
	ASSERT_TRUE(fabs(27 - (r->z)) < EPSILON);
	free(p);
	free(q);
	free(r);

	p = createPoint(76.4, 2.44, 76.9);
	q = createPoint(12.8, 8.23, 9.1);
	r = mult(p, q);
	ASSERT_TRUE(fabs(977.92 - (r->x)) < EPSILON);
	ASSERT_TRUE(fabs(20.0812 - (r->y)) < EPSILON);
	ASSERT_TRUE(fabs(699.79 - (r->z)) < EPSILON);
	free(p);
	free(q);
	free(r);
}

TEST(hermite_multScalar, can_multiply_scalars) {
	pt *p, *r;
	double scalar = 5;
	p = createPoint(7, 8, 9);
	r = multScalar(scalar, p);
	ASSERT_EQ(35, r->x);
	ASSERT_EQ(40, r->y);
	ASSERT_EQ(45, r->z);
	free(p);
	free(r);

	p = createPoint(43.9, 53.87, 12.8);
	scalar = 11;
	r = multScalar(scalar, p);
	ASSERT_TRUE(fabs(482.9 - r->x) < EPSILON);
	ASSERT_TRUE(fabs(592.57 - r->y) < EPSILON);
	ASSERT_TRUE(fabs(140.8 - r->z) < EPSILON);
	free(p);
	free(r);
}

TEST(hermite_getDistance, can_get_distance) {
	pt *p, *q;
	p = createPoint(1, 2, 3);
	q = createPoint(7, 8, 9);
	double dist = getDistance(p, q);
	ASSERT_TRUE(fabs((double)10.392305 - dist) < EPSILON);
}

TEST(hermite_forwardDiff, can_get_forward_diff) {
	struct pt *point1 = createPoint(1, 1, 1);
	struct pt *point2 = createPoint(2, 3, 1);
	struct pt *point3 = minus(point2, point1);
	struct pt *point4 = multScalar(3, point3);
	ASSERT_EQ(3, point4->x);
	ASSERT_EQ(6, point4->y);
	ASSERT_EQ(0, point4->z);
	free(point1);
	free(point2);
	free(point3);
	free(point4);

	point1 = createPoint(-5, 2, -9);
	point2 = createPoint(11, 19, -26);
	point3 = minus(point2, point1);
	point4 = multScalar(3, point3);
	ASSERT_EQ(48, point4->x);
	ASSERT_EQ(51, point4->y);
	ASSERT_EQ(-51, point4->z);
	free(point1);
	free(point2);
	free(point3);
	free(point4);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}