class Solution
{
public:
    int numberOfSteps(int num)
    {
        int steps = 0;

        for (; num; ++steps)
            num = (num & 1) ? num - 1 : num >> 1;

        return steps;
    }
};
