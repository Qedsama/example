using System;

namespace main
{
    class Program
    {
        public class Solution
        {
            public int[] TwoSum(int[] nums, int target)
            {
                string sr = Console.ReadLine();
                char[] s = new char[10000];
                s = sr.ToCharArray();
                target = int.Parse(Console.ReadLine());
                int sa = s.Length, k=0;
                int[] b=new int[100];
                for(int i = 0; i < sa; i++)
                { 
                    if (s[i] >= '0'&&s[i]<'9')
                    {
                        while (s[i] >= '0' && s[i] <= '9')
                        {
                            nums[k] = 10 * nums[k] + s[i++];
                            if (i >= sa) break;
                        }
                        k++;
                    }
                }
                for(int i = 0; i < k; i++)
                {
                    int r = target - nums[i];
                    for(int j = i + 1; j < k; j++)
                    {
                        if (r == nums[j])
                        {
                            b[0] = i;
                            b[1] = j;
                            return b;
                        }
                    }
                }
                return b;
            }
        }
        class Sk
        {
            static void Main(string[] args)
            {
                Solution p = new Solution();
                int[] nums = new int[100]; int target = 0;
                p.TwoSum(nums, target);
            }
        }
    }
}
