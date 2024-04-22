import numpy as np
import torch 
import torch.nn.functional as F 
import tensorflow as tf


def pixel_shuffle(input, upscale_factor):
    batch_size, channels, in_height, in_width = input.shape
    channels //= upscale_factor**2

    out_height = in_height * upscale_factor
    out_width = in_width * upscale_factor

    input_reshaped = input.reshape(
        batch_size, channels, upscale_factor, upscale_factor, in_height, in_width
    )
    input_shuffled = input_reshaped.transpose(0, 1, 4, 2, 5, 3)
    output = input_shuffled.reshape(batch_size, channels, out_height, out_width)

    return output


def test_pixel_shuffle():
    upscale_factor = 2
    in_shape = (4, 3 * upscale_factor * upscale_factor, 32, 64)
    a = np.random.randint(
        1,
        10,
        in_shape,
        dtype=np.int8,
    )
    tensor = torch.Tensor(a)
    out_torch = F.pixel_shuffle(tensor, upscale_factor)
    out_np = pixel_shuffle(a, upscale_factor)
    np.testing.assert_equal(out_np, out_torch)


def space_to_depth(x, block_size):
    x = np.asarray(x)
    batch, height, width, depth = x.shape
    reduced_height = height // block_size
    reduced_width = width // block_size
    # Reshape and transpose to interleave spatial and depth dimensions
    y = x.reshape(batch, reduced_height, block_size, reduced_width, block_size, depth)
    z = y.transpose(0, 1, 3, 2, 4, 5)
    out = z.reshape(batch, reduced_height, reduced_width, -1)
    return out


def test_space_to_depth():
    x = np.array([[[[1], [2]], [[3], [4]]]])
    block_size = 2

    out_np = space_to_depth(x, block_size)
    out_tf = tf.nn.space_to_depth(x, block_size)
    print(x.shape, out_np.shape)
    np.testing.assert_equal(out_np, out_tf)


def depth_to_space(input, block_size):
    input = np.asarray(input)
    batch, height, width, depth = input.shape
    reduced_depth = depth // (block_size**2)

    x = input.reshape(batch, height, width, reduced_depth, block_size, block_size)
    y = x.transpose(0, 1, 4, 2, 5, 3)
    out = y.reshape(batch, height * block_size, width * block_size, reduced_depth)

    return out


def test_depth_to_space():
    input_data = np.random.rand(1, 2, 2, 4)  # Replace with your input
    block_size = 2  # Replace with your block size

    out_np = depth_to_space(input_data, block_size)
    out_tf = tf.nn.depth_to_space(input_data, block_size)
    np.testing.assert_equal(out_np, out_tf)
