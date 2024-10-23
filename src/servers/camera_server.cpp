#include "camera_server.h"

namespace CameraServer {
// Stream handler
static esp_err_t stream_handler(httpd_req_t *req) {
  camera_fb_t *frame_buffer = NULL;
  esp_err_t response = ESP_OK;
  size_t _jpg_buf_len = 0;
  uint8_t *_jpg_buf = NULL;
  char *part_buf[64];

  response = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);

  if (response != ESP_OK) {
    return response;
  }

  while (true) {
    frame_buffer = esp_camera_fb_get();
    if (!frame_buffer) {
      Serial.println("Camera capture failed");
      response = ESP_FAIL;
    } else {
      if (frame_buffer->width > 400) {
        if (frame_buffer->format != PIXFORMAT_JPEG) {
          bool jpeg_converted =
              frame2jpg(frame_buffer, 80, &_jpg_buf, &_jpg_buf_len);
          esp_camera_fb_return(frame_buffer);
          frame_buffer = NULL;
          if (!jpeg_converted) {
            Serial.println("JPEG compression failed");
            response = ESP_FAIL;
          }
        } else {
          _jpg_buf_len = frame_buffer->len;
          _jpg_buf = frame_buffer->buf;
        }
      }
    }
    if (response == ESP_OK) {
      size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
      response = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
    }
    if (response == ESP_OK) {
      response =
          httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
    }
    if (response == ESP_OK) {
      response = httpd_resp_send_chunk(req, _STREAM_BOUNDARY,
                                       strlen(_STREAM_BOUNDARY));
    }
    if (frame_buffer) {
      esp_camera_fb_return(frame_buffer);
      frame_buffer = NULL;
      _jpg_buf = NULL;
    } else if (_jpg_buf) {
      free(_jpg_buf);
      _jpg_buf = NULL;
    }
    if (response != ESP_OK) {
      break;
    }
  }
  return response;
}

// Start http server
void startStream(httpd_handle_t stream_httpd) {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 8090;
  httpd_uri_t index_uri = {.uri = "/",
                           .method = HTTP_GET,
                           .handler = stream_handler,
                           .user_ctx = NULL};

  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &index_uri);
  }
}

void startCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 15;
  config.fb_count = 2;

  // Start the camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

void stopStream(httpd_handle_t stream_httpd) {
  httpd_stop(stream_httpd);
  stream_httpd = NULL;
  esp_camera_deinit();
}
} // namespace CameraServer
